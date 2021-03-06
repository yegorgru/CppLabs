/**
\file
\brief main cpp file

main function, unit tests, random functions and + operators for some classes are here
*/



#include "TestFramework.h"
#include "Book.h"
#include "Profile.h"
#include "BookCharacter.h"
#include "PublishingHouse.h"
#include "Date.h"
#include "Graph.h"
#include "AdjacencyMatrix.h"
#include "AdjacencyStructure.h"

#include <string>
#include <vector>
#include <random>
#include <cmath>
#include <set>


/**
mersenne generates random numbers (better than std::rand)
*/
std::random_device rd;
std::mt19937 mersenne(rd());

/**
\return random string with 10 characters
*/
std::string random_element(std::string) {
	std::string answer;
	for (int i = 0; i < 10; i++) {
		answer.push_back(65 + mersenne() % 26);
	}
	return answer;
}

/**
\return random int <100 and >=0
*/
int random_element(int) {
	return mersenne() % 100;
}

/**
\return random double <1000 and >=0
*/
double random_element(double) {
	return mersenne() % 1000*std::pow(10,0-mersenne()%3);
}

/**
\return random vector with 10 elements
*/
template <typename T>
std::vector<T> random_element(std::vector<T>) {
	std::vector<T>answer(10);
	for (size_t i = 0; i < 10; i++) {
		answer[i] = random_element(T());
	}
	return answer;
}

/**
\return random Role (episodic, secondary or main)
*/
Role random_element(Role) {
	switch (mersenne() % 3) {
	case 0:
		return Role::episodic;
	case 1:
		return Role::secondary;
	case 2:
		return Role::main;
	}
	return Role::secondary;
}

/**
\return random BookCharacter with 3 names and 5 roles in books
*/
template <typename T>
BookCharacter<T> random_element(BookCharacter<T>) {
	std::set<std::string>names;
	for (size_t i = 0; i < mersenne() % 3; i++) {
		names.insert(random_element(std::string()));
	}
	BookCharacter<T>answer(random_element(std::string()), names);
	for (size_t i = 0; i < 5; i++) {
		answer.update_role(random_element(T()), random_element(Role()));
	}
	return answer;
}

/**
\return random valid Date
*/
Date random_element(Date) {
	Date date(mersenne() % 60, mersenne() % 60, mersenne() % 24, mersenne() % 31 + 1, mersenne() % 12 + 1, mersenne() % 2040);
	while (!date.is_valid()) {
		date.set_day(date.get_day() - 1);
	}
	return date;
}

/**
\return random Book (3 authors)
*/
Book random_element(Book) {
	std::set<std::string>authors;
	for (size_t i = 0; i < mersenne() % 3; i++) {
		authors.insert(random_element(std::string()));
	}
	return Book(random_element(std::string()), authors, random_element(Date()), mersenne() % 100 + 1, random_element(std::string()));
}

/**
\return random PublishingHouse with 10 Books and 10 BookCharacters (characters will not be added in books)
*/
PublishingHouse random_element(PublishingHouse) {
	PublishingHouse PH;
	for (size_t i = 0; i < mersenne() % 10; i++) {
		PH.add_book(random_element(Book()));
	}
	for (size_t i = 0; i < mersenne() % 10; i++) {
		PH.add_character(random_element(BookCharacter<std::string>()));
	}
	return PH;
}

/**
Operator + for vectors
*/
template <typename T>
std::vector<T> operator+(const std::vector<T>& lhs, const std::vector<T>& rhs) {
	std::vector<T> answer(lhs.begin(), lhs.end());
	answer.insert(answer.end(),rhs.begin(), rhs.end());
	return answer;
}

/**
Operator + for Dates

\return lhs Date, promote on difference between rhs Date and lhs date in seconds
*/
Date operator+(const Date& lhs, const Date& rhs) {
	if (lhs == Date()) {
		return rhs;
	}
	else if (rhs == Date()) {
		return lhs;
	}
	else {
		Date date = lhs;
		date.promote(lhs.difference(rhs, MeasureTime::seconds), MeasureTime::seconds);
		return date;
	}
}

/**
Operator + for Books

\return Book with fields - sum of fields 0f lhs and rhs
*/
Book operator+(const Book& lhs, const Book& rhs) {
	auto lauthors = lhs.get_authors();
	auto rauthors = rhs.get_authors();
	std::set<std::string>authors(lauthors.begin(), lauthors.end());
	authors.insert(rauthors.begin(), rauthors.end());
	return Book (lhs.get_name() + rhs.get_name(), authors, lhs.get_date()+rhs.get_date(), lhs.get_pages() + rhs.get_pages(), lhs.get_annotation() + rhs.get_annotation());
}


/**
\brief tests BookCharacter<T>
*/
template<typename T>
void TestCharacter() {
	//Test Constructors
	{
		BookCharacter<T> character("Kotygoroshko");
		ASSERT_EQUAL(character.get_default_name(), "Kotygoroshko");
		ASSERT_EQUAL(character.get_all_names(),
			std::set<std::string>{ "Kotygoroshko" });
	}
	{
		std::set<std::string> names{ "Harry", "Potter", "a boy who survived" };
		BookCharacter<T> character("Harry Potter", names);
		ASSERT_EQUAL(character.get_default_name(), "Harry Potter");
		ASSERT_EQUAL(character.get_all_names(),names);


		//Test methods
		character.erase_name("Harry");
		names.erase("Harry");
		ASSERT_EQUAL(character.get_all_names(), names);

		character.add_name("Harry");
		names.insert("Harry");
		ASSERT_EQUAL(character.get_all_names(), names);

		character.set_names({ "Potter" });
		names = { "Potter","Harry Potter" };
		ASSERT_EQUAL(character.get_all_names(), names);

		auto random_book = random_element(T());
		character.update_role(random_book, Role::main);
		ASSERT_EQUAL(character.get_role(random_book), Role::main);

		character.update_role(random_book, Role::secondary);
		ASSERT_EQUAL(character.get_role(random_book), Role::secondary);

		character.decrease(random_book);
		ASSERT_EQUAL(character.get_role(random_book), Role::episodic);

		character.decrease(random_book);
		ASSERT_EQUAL(character.get_role(random_book), Role::episodic);

		character.promote(random_book);
		character.promote(random_book);
		ASSERT_EQUAL(character.get_role(random_book), Role::main);

		character.promote(random_book);
		ASSERT_EQUAL(character.get_role(random_book), Role::main);

		auto books = character.get_all_books();
		ASSERT_EQUAL(books, std::set<T>{ random_book });

		auto random_book2 = random_element(T());
		auto random_book3 = random_element(T());
		character.update_role(random_book2, Role::main);
		character.update_role(random_book3, Role::episodic);
		books.insert(random_book3);
		books.insert(random_book2);

		ASSERT_EQUAL(character.get_all_books(), books);

		character.erase_book(random_book2);
		books.erase(random_book2);

		ASSERT_EQUAL(character.get_all_books(), books);
	}
}

/**
\brief tests BookCharacters (int and std::string)
*/
void TestBookCharacter() {
	TestCharacter<std::string>();
	TestCharacter<int>();
}

/**
\brief tests Books
*/
void TestBook() {
	Book book("Chamber of Secrets", { "J. K. Rowling" },
		Date(1, 1, 1, 1, 1, 2005), 400,
		"second book about Harry Potter, small wizard");
	ASSERT_EQUAL("Chamber of Secrets", book.get_name());
	ASSERT_EQUAL(std::set<std::string>{ "J. K. Rowling" }, book.get_authors());
	ASSERT_EQUAL(Date(1, 1, 1, 1, 1, 2005), book.get_date());
	ASSERT_EQUAL(400, book.get_pages());
	ASSERT_EQUAL("second book about Harry Potter, small wizard",
		book.get_annotation());

	book.erase_author("J. K. Rowling");
	ASSERT_EQUAL(std::set<std::string>{}, book.get_authors());

	book.add_author("T. Shevchenko");
	ASSERT_EQUAL(std::set<std::string>{"T. Shevchenko"}, book.get_authors());

	std::set<std::string> authors{ "J. K. Rowling" ,"Baron Munchausen" };
	book.set_authors(authors);
	ASSERT_EQUAL(authors, book.get_authors());

	Date new_date(2, 2, 2, 2, 2, 2020);
	book.set_date(new_date);
	ASSERT_EQUAL(new_date, book.get_date());

	book.set_pages(200);
	ASSERT_EQUAL(200, book.get_pages());

	book.set_annotation("small annotation");
	ASSERT_EQUAL("small annotation", book.get_annotation());
}


/**
\brief tests PublishingHouse::get_series
*/
void TestHouseSeries() {
	{
		PublishingHouse PHouse;

		//Empty series
		auto series = PHouse.get_series();
		ASSERT_EQUAL(series, std::vector<std::vector<Book>>{});

		//1 series with 1 book without characters
		Book first_book("Book", { "" }, Date(1, 1, 1, 1, 1, 1), 10, "");
		auto first_book_id = PHouse.add_book(first_book);
		series = PHouse.get_series();
		ASSERT_EQUAL(series, std::vector<std::vector<Book>> { {first_book} });

		//1 series with 3 books without characters
		Book second_book("Book2", { "" }, Date(1, 1, 1, 1, 0, 1), 10, "");
		Book third_book("Book3", { "" }, Date(1, 1, 1, 0, 1, 1), 10, "");
		auto second_book_id = PHouse.add_book(second_book);
		auto third_book_id = PHouse.add_book(third_book);
		std::vector<std::vector<Book>> true_series{ {second_book, third_book, first_book} };
		series = PHouse.get_series();
		ASSERT_EQUAL(series, true_series);

		//1 unimportant character
		auto character_id = PHouse.add_character(BookCharacter<std::string>("First character"));
		PHouse.add_character_in_book(character_id, first_book_id, Role::episodic);
		series = PHouse.get_series();
		ASSERT_EQUAL(series, true_series);

		//1 important character, 2 series
		PHouse.promote_role(character_id, first_book_id);
		series = PHouse.get_series();
		true_series = {
			{first_book},
			{second_book,third_book}
		};
		ASSERT_EQUAL(series, true_series);

		//new book in series with character
		PHouse.add_character_in_book(character_id, second_book_id, Role::main);
		series = PHouse.get_series();
		true_series = {
			{third_book},
			{second_book,first_book}
		};
		ASSERT_EQUAL(series, true_series);
	}
	{
		//3 books, 2 characters
		PublishingHouse PHouse;
		Book first_book("Book", { "" }, Date(1, 1, 1, 1, 1, 1), 10, "");
		auto first_book_id = PHouse.add_book(first_book);
		Book second_book("Book2", { "" }, Date(1, 1, 1, 1, 0, 1), 10, "");
		Book third_book("Book3", { "" }, Date(1, 1, 1, 0, 1, 1), 10, "");
		auto second_book_id = PHouse.add_book(second_book);
		auto third_book_id = PHouse.add_book(third_book);
		auto first_character_id = PHouse.add_character(BookCharacter<std::string>("First character"));
		auto second_character_id = PHouse.add_character(BookCharacter<std::string>("Second character"));
		PHouse.add_character_in_book(first_character_id, first_book_id, Role::episodic);
		PHouse.add_character_in_book(second_character_id, second_book_id, Role::secondary);
		PHouse.add_character_in_book(first_character_id, second_book_id, Role::main);
		PHouse.add_character_in_book(second_character_id, third_book_id, Role::secondary);
		auto series = PHouse.get_series();
		std::vector<std::vector<Book>>true_series = {
			{first_book},
			{second_book,third_book}
		};
		ASSERT_EQUAL(series, true_series);


		PHouse.promote_role(first_character_id, first_book_id);
		series = PHouse.get_series();
		true_series = {
			{second_book, third_book, first_book}
		};
		ASSERT_EQUAL(series, true_series);

		PHouse.decrease_role(second_character_id, third_book_id);
		series = PHouse.get_series();
		true_series = {
			{third_book},
			{second_book,first_book}
		};
		ASSERT_EQUAL(series, true_series);
	}
	{
		//3 books, 3 characters
		PublishingHouse PHouse;
		Book first_book("A", { "" }, Date(1, 1, 1, 1, 1, 1), 10, "");
		auto first_book_id = PHouse.add_book(first_book);
		Book second_book("B", { "" }, Date(1, 1, 1, 1, 0, 1), 10, "");
		Book third_book("C", { "" }, Date(1, 1, 1, 0, 1, 1), 10, "");
		auto second_book_id = PHouse.add_book(second_book);
		auto third_book_id = PHouse.add_book(third_book);
		auto first_character_id = PHouse.add_character(BookCharacter<std::string>("First character"));
		auto second_character_id = PHouse.add_character(BookCharacter<std::string>("Second character"));
		auto third_character_id = PHouse.add_character(BookCharacter<std::string>("Third character"));
		PHouse.add_character_in_book(first_character_id, first_book_id, Role::secondary);
		PHouse.add_character_in_book(first_character_id, second_book_id, Role::secondary);
		PHouse.add_character_in_book(first_character_id, third_book_id, Role::secondary);
		PHouse.add_character_in_book(second_character_id, second_book_id, Role::secondary);
		PHouse.add_character_in_book(second_character_id, third_book_id, Role::secondary);
		PHouse.add_character_in_book(third_character_id, third_book_id, Role::secondary);
		auto series = PHouse.get_series();
		std::vector<std::vector<Book>>true_series = {
			{second_book, third_book, first_book}
		};
		ASSERT_EQUAL(series, true_series);
	}
	{
		//9 books, 3 characters
		PublishingHouse PHouse;
		Book A("A", { "" }, Date(9, 1, 1, 1, 1, 1), 10, "");
		auto first_book_id = PHouse.add_book(A);
		Book B("B", { "" }, Date(8, 1, 1, 1, 1, 1), 10, "");
		auto second_book_id = PHouse.add_book(B);
		Book C("C", { "" }, Date(7, 1, 1, 1, 1, 1), 10, "");
		auto third_book_id = PHouse.add_book(C);
		Book D("D", { "" }, Date(6, 1, 1, 1, 1, 1), 10, "");
		auto fourth_book_id = PHouse.add_book(D);
		Book E("E", { "" }, Date(5, 1, 1, 1, 1, 1), 10, "");
		auto fifth_book_id = PHouse.add_book(E);
		Book F("F", { "" }, Date(4, 1, 1, 1, 1, 1), 10, "");
		auto sixth_book_id = PHouse.add_book(F);
		Book G("G", { "" }, Date(3, 1, 1, 1, 1, 1), 10, "");
		auto seventh_book_id = PHouse.add_book(G);
		Book H("H", { "" }, Date(2, 1, 1, 1, 1, 1), 10, "");
		auto eighth_book_id = PHouse.add_book(H);
		Book I("I", { "" }, Date(1, 1, 1, 1, 1, 1), 10, "");
		auto ninth_book_id = PHouse.add_book(I);
		auto first_character_id = PHouse.add_character(BookCharacter<std::string>("First character"));
		auto second_character_id = PHouse.add_character(BookCharacter<std::string>("Second character"));
		auto third_character_id = PHouse.add_character(BookCharacter<std::string>("Third character"));
		
		PHouse.add_character_in_book(first_character_id, ninth_book_id, Role::secondary);
		PHouse.add_character_in_book(second_character_id, eighth_book_id, Role::secondary);
		PHouse.add_character_in_book(third_character_id, seventh_book_id, Role::secondary);
		PHouse.add_character_in_book(first_character_id, sixth_book_id, Role::secondary);
		PHouse.add_character_in_book(second_character_id, fifth_book_id, Role::secondary);
		PHouse.add_character_in_book(third_character_id, fourth_book_id, Role::secondary);
		PHouse.add_character_in_book(first_character_id, third_book_id, Role::secondary);
		PHouse.add_character_in_book(second_character_id, second_book_id, Role::secondary);
		PHouse.add_character_in_book(third_character_id, first_book_id, Role::secondary);

		auto series = PHouse.get_series();
		std::vector<std::vector<Book>>true_series = {
			{G, D, A},
			{H, E, B},
			{I, F, C}
		};
		ASSERT_EQUAL(series, true_series);

		//merge 1 and 2 series
		PHouse.add_character_in_book(third_character_id, fifth_book_id, Role::main);
		series = PHouse.get_series();
		true_series = {
			{I, F, C},
			{H,G, E,D, B,A}
		};
		ASSERT_EQUAL(series, true_series);

		//merge series
		PHouse.add_character_in_book(second_character_id, ninth_book_id, Role::main);
		series = PHouse.get_series();
		true_series = {
			{I,H,G,F, E,D,C, B,A}
		};
		ASSERT_EQUAL(series, true_series);

		//split series
		PHouse.erase_character_from_book(second_character_id, fifth_book_id);
		series = PHouse.get_series();
		true_series = {
			{G,E,D,A},
			{I,H,F,C,B}
		};
		ASSERT_EQUAL(series, true_series);

		//split 2 series
		PHouse.erase_character_from_book(first_character_id, ninth_book_id);
		series = PHouse.get_series();
		true_series = {
			{F,C},
			{I,H,B},
			{G,E,D,A}
		};
		ASSERT_EQUAL(series, true_series);
	}
}

/**
\brief tests PublishingHouse methods except PublishingHouse::get_series
*/
void TestHouseNotSeries() {

	//get characters, get important characters, promote role, decrease role, get role
	{
		PublishingHouse PHouse;
		Book first_book("A", { "" }, Date(1, 1, 1, 1, 1, 1), 10, "");
		auto first_book_id = PHouse.add_book(first_book);
		auto first_character_id = PHouse.add_character(BookCharacter<std::string>("First character"));
		auto second_character_id = PHouse.add_character(BookCharacter<std::string>("Second character"));
		std::set<std::string> true_characters{};
		std::set<std::string> characters = PHouse.get_characters(first_book_id);
		ASSERT_EQUAL(characters, true_characters);
		characters = PHouse.get_important_characters(first_book_id);
		ASSERT_EQUAL(characters, true_characters);

		PHouse.add_character_in_book(first_character_id, first_book_id, Role::main);
		PHouse.add_character_in_book(second_character_id, first_book_id, Role::episodic);
		true_characters.insert(first_character_id);
		characters = PHouse.get_important_characters(first_book_id);
		ASSERT_EQUAL(characters, true_characters);

		ASSERT_EQUAL(PHouse.get_role(first_character_id, first_book_id), Role::main);
		PHouse.promote_role(first_character_id, first_book_id);
		ASSERT_EQUAL(PHouse.get_role(first_character_id, first_book_id), Role::main);
		ASSERT_EQUAL(PHouse.get_role(second_character_id, first_book_id), Role::episodic);
		PHouse.decrease_role(second_character_id, first_book_id);
		ASSERT_EQUAL(PHouse.get_role(second_character_id, first_book_id), Role::episodic);

		true_characters.insert(second_character_id);
		characters = PHouse.get_characters(first_book_id);
		ASSERT_EQUAL(characters, true_characters);

		PHouse.promote_role(second_character_id, first_book_id);
		characters = PHouse.get_important_characters(first_book_id);
		ASSERT_EQUAL(characters, true_characters);

		PHouse.decrease_role(first_character_id, first_book_id);
		characters = PHouse.get_important_characters(first_book_id);
		ASSERT_EQUAL(characters, true_characters);

		PHouse.decrease_role(first_character_id, first_book_id);
		characters = PHouse.get_important_characters(first_book_id);
		true_characters.erase(first_character_id);
		ASSERT_EQUAL(characters, true_characters);

		ASSERT_EQUAL(PHouse.get_role(first_character_id, first_book_id), Role::episodic);
		ASSERT_EQUAL(PHouse.get_role(second_character_id, first_book_id), Role::secondary);
	}
	//get books, add role, erase role, get book, get character,add character, add book
	{
		PublishingHouse PHouse;
		Book first_book("A", { "Author1" }, Date(1, 49, 1, 1, 1, 1), 345, "");
		auto first_book_id = PHouse.add_book(first_book);
		ASSERT_EQUAL(first_book, PHouse.get_book(first_book_id));

		Book second_book("B", { "Author1","Author2" }, Date(1, 1, 1, 1, 1, 1), 100, "dgfhf");
		auto second_book_id = PHouse.add_book(second_book);
		ASSERT_EQUAL(second_book, PHouse.get_book(second_book_id));

		Book third_book("C", { "" }, Date(1, 1, 10, 1, 45, 1), 15, "xfbdgnfgn");
		auto third_book_id = PHouse.add_book(third_book);
		ASSERT_EQUAL(third_book, PHouse.get_book(third_book_id));

		BookCharacter<std::string> character1("First character", { "A","B" });
		auto first_character_id = PHouse.add_character(character1);
		BookCharacter<std::string> character2("Second character");
		auto second_character_id = PHouse.add_character(character2);

		ASSERT_EQUAL(PHouse.get_character(first_character_id), character1);
		ASSERT_EQUAL(PHouse.get_character(second_character_id), character2);

		std::set<std::string>true_books = {};
		ASSERT_EQUAL(true_books, PHouse.get_books(first_character_id));

		PHouse.add_character_in_book(first_character_id, first_book_id, Role::secondary);
		true_books.insert(first_book_id);
		ASSERT_EQUAL(true_books, PHouse.get_books(first_character_id));

		PHouse.add_character_in_book(first_character_id, second_book_id, Role::secondary);
		true_books.insert(second_book_id);
		ASSERT_EQUAL(true_books, PHouse.get_books(first_character_id));
		ASSERT_EQUAL(std::set<std::string>{first_character_id}, PHouse.get_characters(first_book_id));

		PHouse.erase_character_from_book(first_character_id, first_book_id);
		true_books.erase(first_book_id);
		ASSERT_EQUAL(true_books, PHouse.get_books(first_character_id));
		ASSERT_EQUAL(std::set<std::string>{}, PHouse.get_characters(first_book_id));
	}
	//ban character, ban role
	{
		PublishingHouse PHouse;
		Book first_book("A", { "" }, Date(1, 1, 1, 1, 1, 1), 10, "");
		auto first_book_id = PHouse.add_book(first_book);
		Book second_book("B", { "" }, Date(1, 1, 1, 1, 1, 1), 10, "");
		auto second_book_id = PHouse.add_book(second_book);
		BookCharacter<std::string> character1("First character");
		auto first_character_id = PHouse.add_character(character1);
		BookCharacter<std::string> character2("Second character");
		auto second_character_id = PHouse.add_character(character2);
		BookCharacter<std::string> character3("Third character");
		auto third_character_id = PHouse.add_character(character3);
		PHouse.add_character_in_book(first_character_id, first_book_id, Role::main);
		PHouse.add_character_in_book(first_character_id, second_book_id, Role::main);
		PHouse.add_character_in_book(second_character_id, first_book_id, Role::main);
		PHouse.add_character_in_book(second_character_id, second_book_id, Role::main);
		PHouse.add_character_in_book(third_character_id, first_book_id, Role::main);
		PHouse.add_character_in_book(third_character_id, second_book_id, Role::main);
		std::set<std::string>true_books = { first_book_id, second_book_id };
		ASSERT_EQUAL(PHouse.get_books(first_character_id), true_books);
		std::set<std::string>true_characters = { first_character_id,
			second_character_id,third_character_id };
		ASSERT_EQUAL(PHouse.get_characters(first_book_id), true_characters);

		PHouse.ban_book(second_book_id);
		true_books.erase(second_book_id);
		ASSERT_EQUAL(PHouse.get_books(first_character_id), true_books);
		PHouse.ban_character(second_character_id);
		true_characters.erase(second_character_id);
		ASSERT_EQUAL(PHouse.get_characters(first_book_id), true_characters);
		PHouse.ban_character(first_character_id);
		true_characters.erase(first_character_id);
		ASSERT_EQUAL(PHouse.get_characters(first_book_id), true_characters);
		PHouse.ban_book(first_book_id);
		true_books.erase(first_book_id);
		ASSERT_EQUAL(PHouse.get_books(third_character_id), true_books);
	}
}

/**
\brief launches tests for PublishingHouse
*/
void TestHouse() {
	TestHouseNotSeries();
	TestHouseSeries();
}

/**
\brief tests basic methods of Date (getters, setters, basic constructor)
*/
void TestDateBasic() {
	Date date(1, 2, 3, 4, 5, 6);
	ASSERT_EQUAL(date.get_year(), 6);
	date.set_year(7);
	ASSERT_EQUAL(date.get_year(), 7);
	ASSERT_EQUAL(date.get_month(), 5);
	date.set_month(6);
	ASSERT_EQUAL(date.get_month(), 6);
	ASSERT_EQUAL(date.get_day(), 4);
	date.set_day(5);
	ASSERT_EQUAL(date.get_day(), 5);
	ASSERT_EQUAL(date.get_hours(), 3);
	date.set_hours(4);
	ASSERT_EQUAL(date.get_hours(), 4);
	ASSERT_EQUAL(date.get_minutes(), 2);
	date.set_minutes(3);
	ASSERT_EQUAL(date.get_minutes(), 3);
	ASSERT_EQUAL(date.get_seconds(), 1);
	date.set_seconds(2);
	ASSERT_EQUAL(date.get_seconds(), 2);

	Date another = date;
	ASSERT_EQUAL(another.get_year(), 7);
	ASSERT_EQUAL(another.get_month(), 6);
	ASSERT_EQUAL(another.get_day(), 5);
	ASSERT_EQUAL(another.get_hours(), 4);
	ASSERT_EQUAL(another.get_minutes(), 3);
	ASSERT_EQUAL(another.get_seconds(), 2);
}

/**
\brief tests Date::is_leap and Date::count_29_february
*/
void TestDateLeap() {
	ASSERT(Date(1, 1, 1, 1, 1, 2020).is_leap());
	ASSERT(Date(1, 1, 1, 1, 1, 2024).is_leap());
	ASSERT(Date(1, 1, 1, 1, 1, 2000).is_leap());
	ASSERT(Date(1, 1, 1, 1, 1, 2096).is_leap());
	ASSERT(Date(1, 1, 1, 1, 1, 4).is_leap());
	ASSERT(!(Date(1, 1, 1, 1, 1, 3).is_leap()));
	ASSERT(!(Date(1, 1, 1, 1, 1, 2100).is_leap()));
	ASSERT(!(Date(1, 1, 1, 1, 1, 2200).is_leap()));
	ASSERT(!(Date(1, 1, 1, 1, 1, 2300).is_leap()));
	ASSERT(!(Date(1, 1, 1, 1, 1, 2021).is_leap()));

	{
		Date basis(1, 1, 1, 1, 1, 2020);
		ASSERT_EQUAL(0, basis.count_29_february(Date(1, 1, 1, 1, 1, 2020)));
		ASSERT_EQUAL(0, basis.count_29_february(Date(1, 1, 1, 29, 2, 2020)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 3, 2020)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 1, 2021)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 1, 2022)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 1, 2023)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 1, 2024)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 29, 2, 2024)));
		ASSERT_EQUAL(2, basis.count_29_february(Date(1, 1, 1, 1, 3, 2024)));
		ASSERT_EQUAL(2, basis.count_29_february(Date(1, 1, 1, 1, 1, 2025)));
		ASSERT_EQUAL(7, basis.count_29_february(Date(1, 1, 1, 1, 1, 2045)));
	}
	{
		Date basis(1, 1, 1, 1, 1, 2000);
		ASSERT_EQUAL(0, basis.count_29_february(Date(1, 1, 1, 28, 2, 2000)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 3, 2000)));
		ASSERT_EQUAL(2, basis.count_29_february(Date(1, 1, 1, 1, 1, 2005)));
	}
	{
		Date basis(1, 1, 1, 1, 1, 2100);
		ASSERT_EQUAL(0, basis.count_29_february(Date(1, 1, 1, 28, 2, 2100)));
		ASSERT_EQUAL(0, basis.count_29_february(Date(1, 1, 1, 1, 3, 2100)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 1, 2105)));
	}
	{
		Date basis(1, 1, 1, 1, 1, 2400);
		ASSERT_EQUAL(0, basis.count_29_february(Date(1, 1, 1, 28, 2, 2400)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 3, 2400)));
		ASSERT_EQUAL(2, basis.count_29_february(Date(1, 1, 1, 1, 1, 2405)));
	}
	{
		Date basis(1, 1, 1, 1, 1, 2000);
		ASSERT_EQUAL(25, basis.count_29_february(Date(1, 1, 1, 1, 1, 2100)));
		ASSERT_EQUAL(25, basis.count_29_february(Date(1, 1, 1, 1, 3, 2100)));
		ASSERT_EQUAL(49, basis.count_29_february(Date(1, 1, 1, 1, 1, 2200)));
		ASSERT_EQUAL(49, basis.count_29_february(Date(1, 1, 1, 1, 3, 2200)));
		ASSERT_EQUAL(73, basis.count_29_february(Date(1, 1, 1, 1, 1, 2300)));
		ASSERT_EQUAL(73, basis.count_29_february(Date(1, 1, 1, 1, 3, 2300)));
		ASSERT_EQUAL(97, basis.count_29_february(Date(1, 1, 1, 1, 1, 2400)));
		ASSERT_EQUAL(98, basis.count_29_february(Date(1, 1, 1, 1, 3, 2400)));
		ASSERT_EQUAL(122, basis.count_29_february(Date(1, 1, 1, 1, 1, 2500)));
		ASSERT_EQUAL(122, basis.count_29_february(Date(1, 1, 1, 1, 3, 2500)));
	}
	{
		Date basis(1, 1, 1, 31, 12, 2019);
		ASSERT_EQUAL(0, basis.count_29_february(Date(1, 1, 1, 1, 1, 2020)));
		ASSERT_EQUAL(0, basis.count_29_february(Date(1, 1, 1, 29, 2, 2020)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 3, 2020)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 1, 2021)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 1, 2022)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 1, 2023)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 1, 2024)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 29, 2, 2024)));
		ASSERT_EQUAL(2, basis.count_29_february(Date(1, 1, 1, 1, 3, 2024)));
		ASSERT_EQUAL(2, basis.count_29_february(Date(1, 1, 1, 1, 1, 2025)));
		ASSERT_EQUAL(7, basis.count_29_february(Date(1, 1, 1, 1, 1, 2045)));
	}
	{
		Date basis(1, 1, 1, 31, 12, 1999);
		ASSERT_EQUAL(0, basis.count_29_february(Date(1, 1, 1, 28, 2, 2000)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 3, 2000)));
		ASSERT_EQUAL(2, basis.count_29_february(Date(1, 1, 1, 1, 1, 2005)));

		ASSERT_EQUAL(25, basis.count_29_february(Date(1, 1, 1, 1, 1, 2100)));
		ASSERT_EQUAL(25, basis.count_29_february(Date(1, 1, 1, 1, 3, 2100)));
		ASSERT_EQUAL(49, basis.count_29_february(Date(1, 1, 1, 1, 1, 2200)));
		ASSERT_EQUAL(49, basis.count_29_february(Date(1, 1, 1, 1, 3, 2200)));
		ASSERT_EQUAL(73, basis.count_29_february(Date(1, 1, 1, 1, 1, 2300)));
		ASSERT_EQUAL(73, basis.count_29_february(Date(1, 1, 1, 1, 3, 2300)));
		ASSERT_EQUAL(97, basis.count_29_february(Date(1, 1, 1, 1, 1, 2400)));
		ASSERT_EQUAL(98, basis.count_29_february(Date(1, 1, 1, 1, 3, 2400)));
		ASSERT_EQUAL(122, basis.count_29_february(Date(1, 1, 1, 1, 1, 2500)));
		ASSERT_EQUAL(122, basis.count_29_february(Date(1, 1, 1, 1, 3, 2500)));
	}
	{
		Date basis(1, 1, 1, 31, 12, 2099);
		ASSERT_EQUAL(0, basis.count_29_february(Date(1, 1, 1, 28, 2, 2100)));
		ASSERT_EQUAL(0, basis.count_29_february(Date(1, 1, 1, 1, 3, 2100)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 1, 2105)));
	}

	{
		Date basis(1, 1, 1, 1, 1, 2019);
		ASSERT_EQUAL(0, basis.count_29_february(Date(1, 1, 1, 1, 1, 2020)));
		ASSERT_EQUAL(0, basis.count_29_february(Date(1, 1, 1, 29, 2, 2020)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 3, 2020)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 1, 2021)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 1, 2022)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 1, 2023)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 1, 2024)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 29, 2, 2024)));
		ASSERT_EQUAL(2, basis.count_29_february(Date(1, 1, 1, 1, 3, 2024)));
		ASSERT_EQUAL(2, basis.count_29_february(Date(1, 1, 1, 1, 1, 2025)));
		ASSERT_EQUAL(7, basis.count_29_february(Date(1, 1, 1, 1, 1, 2045)));
	}
	{
		Date basis(1, 1, 1, 1, 1, 1999);
		ASSERT_EQUAL(0, basis.count_29_february(Date(1, 1, 1, 28, 2, 2000)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 3, 2000)));
		ASSERT_EQUAL(2, basis.count_29_february(Date(1, 1, 1, 1, 1, 2005)));

		ASSERT_EQUAL(25, basis.count_29_february(Date(1, 1, 1, 1, 1, 2100)));
		ASSERT_EQUAL(25, basis.count_29_february(Date(1, 1, 1, 1, 3, 2100)));
		ASSERT_EQUAL(49, basis.count_29_february(Date(1, 1, 1, 1, 1, 2200)));
		ASSERT_EQUAL(49, basis.count_29_february(Date(1, 1, 1, 1, 3, 2200)));
		ASSERT_EQUAL(73, basis.count_29_february(Date(1, 1, 1, 1, 1, 2300)));
		ASSERT_EQUAL(73, basis.count_29_february(Date(1, 1, 1, 1, 3, 2300)));
		ASSERT_EQUAL(97, basis.count_29_february(Date(1, 1, 1, 1, 1, 2400)));
		ASSERT_EQUAL(98, basis.count_29_february(Date(1, 1, 1, 1, 3, 2400)));
		ASSERT_EQUAL(122, basis.count_29_february(Date(1, 1, 1, 1, 1, 2500)));
		ASSERT_EQUAL(122, basis.count_29_february(Date(1, 1, 1, 1, 3, 2500)));
	}
	{
		Date basis(1, 1, 1, 1, 1, 2099);
		ASSERT_EQUAL(0, basis.count_29_february(Date(1, 1, 1, 28, 2, 2100)));
		ASSERT_EQUAL(0, basis.count_29_february(Date(1, 1, 1, 1, 3, 2100)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 1, 2105)));
	}
	{
		Date basis(1, 1, 1, 1, 3, 2020);
		ASSERT_EQUAL(-1, basis.count_29_february(Date(1, 1, 1, 28, 2, 2020)));
		ASSERT_EQUAL(0, basis.count_29_february(Date(1, 1, 1, 2, 3, 2020)));
		ASSERT_EQUAL(0, basis.count_29_february(Date(1, 1, 1, 29, 2, 2024)));
		ASSERT_EQUAL(1, basis.count_29_february(Date(1, 1, 1, 1, 3, 2024)));
	}
	{
		Date basis(59, 59, 23, 28, 2, 2020);
		ASSERT_EQUAL(1, basis.count_29_february(Date(0, 0, 0, 1, 3, 2020)));
		ASSERT_EQUAL(0, basis.count_29_february(Date(59, 59, 23, 29, 2, 2020)));
		ASSERT_EQUAL(Date(0, 0, 0, 29, 2, 2020).count_29_february(Date(59, 59, 23, 29, 2, 2020)), 0);
	}
}

/**
\brief tests Date::is_valid
*/
void TestDateIsValid() {
	ASSERT(Date(1, 1, 1, 28, 9, 2020).is_valid());

	ASSERT(!(Date(1, 1, 1, 0, 1, 2020).is_valid()));
	ASSERT(Date(1, 1, 1, 1, 1, 2020).is_valid());
	ASSERT(Date(1, 1, 1, 31, 1, 2020).is_valid());
	ASSERT(!(Date(1, 1, 1, 32, 1, 2020).is_valid()));

	ASSERT(!(Date(1, 1, 1, 0, 2, 2020).is_valid()));
	ASSERT(Date(1, 1, 1, 1, 2, 2020).is_valid());
	ASSERT(Date(1, 1, 1, 29, 2, 2020).is_valid());
	ASSERT(!(Date(1, 1, 1, 30, 2, 2020).is_valid()));

	ASSERT(!(Date(1, 1, 1, 0, 2, 2021).is_valid()));
	ASSERT(Date(1, 1, 1, 1, 2, 2021).is_valid());
	ASSERT(Date(1, 1, 1, 28, 2, 2021).is_valid());
	ASSERT(!(Date(1, 1, 1, 29, 2, 2021).is_valid()));

	ASSERT(!(Date(1, 1, 1, 0, 3, 2020).is_valid()));
	ASSERT(Date(1, 1, 1, 1, 3, 2020).is_valid());
	ASSERT(Date(1, 1, 1, 31, 3, 2020).is_valid());
	ASSERT(!(Date(1, 1, 1, 32, 3, 2020).is_valid()));

	ASSERT(!(Date(1, 1, 1, 0, 4, 2020).is_valid()));
	ASSERT(Date(1, 1, 1, 1, 4, 2020).is_valid());
	ASSERT(Date(1, 1, 1, 30, 4, 2020).is_valid());
	ASSERT(!(Date(1, 1, 1, 31, 4, 2020).is_valid()));

	ASSERT(!(Date(1, 1, 1, 0, 5, 2020).is_valid()));
	ASSERT(Date(1, 1, 1, 1, 5, 2020).is_valid());
	ASSERT(Date(1, 1, 1, 31, 5, 2020).is_valid());
	ASSERT(!(Date(1, 1, 1, 32, 5, 2020).is_valid()));

	ASSERT(!(Date(1, 1, 1, 0, 6, 2020).is_valid()));
	ASSERT(Date(1, 1, 1, 1, 6, 2020).is_valid());
	ASSERT(Date(1, 1, 1, 30, 6, 2020).is_valid());
	ASSERT(!(Date(1, 1, 1, 31, 6, 2020).is_valid()));

	ASSERT(!(Date(1, 1, 1, 0, 7, 2020).is_valid()));
	ASSERT(Date(1, 1, 1, 1, 7, 2020).is_valid());
	ASSERT(Date(1, 1, 1, 31, 7, 2020).is_valid());
	ASSERT(!(Date(1, 1, 1, 32, 7, 2020).is_valid()));

	ASSERT(!(Date(1, 1, 1, 0, 8, 2020).is_valid()));
	ASSERT(Date(1, 1, 1, 1, 8, 2020).is_valid());
	ASSERT(Date(1, 1, 1, 31, 8, 2020).is_valid());
	ASSERT(!(Date(1, 1, 1, 32, 8, 2020).is_valid()));

	ASSERT(!(Date(1, 1, 1, 0, 9, 2020).is_valid()));
	ASSERT(Date(1, 1, 1, 1, 9, 2020).is_valid());
	ASSERT(Date(1, 1, 1, 30, 9, 2020).is_valid());
	ASSERT(!(Date(1, 1, 1, 31, 9, 2020).is_valid()));

	ASSERT(!(Date(1, 1, 1, 0, 10, 2020).is_valid()));
	ASSERT(Date(1, 1, 1, 1, 10, 2020).is_valid());
	ASSERT(Date(1, 1, 1, 31, 10, 2020).is_valid());
	ASSERT(!(Date(1, 1, 1, 32, 10, 2020).is_valid()));

	ASSERT(!(Date(1, 1, 1, 0, 11, 2020).is_valid()));
	ASSERT(Date(1, 1, 1, 1, 11, 2020).is_valid());
	ASSERT(Date(1, 1, 1, 30, 11, 2020).is_valid());
	ASSERT(!(Date(1, 1, 1, 31, 11, 2020).is_valid()));

	ASSERT(!(Date(1, 1, 1, 0, 12, 2020).is_valid()));
	ASSERT(Date(1, 1, 1, 1, 12, 2020).is_valid());
	ASSERT(Date(1, 1, 1, 31, 12, 2020).is_valid());
	ASSERT(!(Date(1, 1, 1, 32, 12, 2020).is_valid()));

	ASSERT(!(Date(-1, 1, 1, 1, 12, 2020).is_valid()));
	ASSERT(!(Date(1, -1, 1, 1, 12, 2020).is_valid()));
	ASSERT(!(Date(1, 1, -1, 1, 12, 2020).is_valid()));
	
	ASSERT(!(Date(60, 1, 1, 1, 12, 2020).is_valid()));
	ASSERT(!(Date(1, 60, 1, 1, 12, 2020).is_valid()));
	ASSERT(!(Date(1, 1, 24, 1, 12, 2020).is_valid()));

	ASSERT(Date(0, 1, 1, 1, 12, 2020).is_valid());
	ASSERT(Date(1, 0, 1, 31, 12, 2020).is_valid());
	ASSERT(Date(1, 1, 0, 1, 12, 2020).is_valid());

	ASSERT(Date(59, 1, 1, 31, 12, 2020).is_valid());
	ASSERT(Date(1, 59, 1, 31, 12, 2020).is_valid());
	ASSERT(Date(1, 1, 23, 31, 12, 2020).is_valid());
}

/**
\brief tests Date::get_number_in_year and Date::get_reverse_number_in_year
*/
void TestDateNumberInYear() {
	ASSERT_EQUAL(Date(1, 1, 1, 1, 1, 2019).get_number_in_year(), 1);
	ASSERT_EQUAL(Date(1, 1, 1, 1, 1, 2019).get_reverse_number_in_year(), 365);

	ASSERT_EQUAL(Date(1, 1, 1, 28, 2, 2019).get_number_in_year(), 59);
	ASSERT_EQUAL(Date(1, 1, 1, 28, 2, 2019).get_reverse_number_in_year(), 366-59);

	ASSERT_EQUAL(Date(1, 1, 1, 1, 3, 2019).get_number_in_year(), 60);
	ASSERT_EQUAL(Date(1, 1, 1, 1, 3, 2019).get_reverse_number_in_year(), 366 - 60);

	ASSERT_EQUAL(Date(1, 1, 1, 28, 2, 2020).get_number_in_year(), 59);
	ASSERT_EQUAL(Date(1, 1, 1, 28, 2, 2020).get_reverse_number_in_year(), 367 - 59);

	ASSERT_EQUAL(Date(1, 1, 1, 29, 2, 2020).get_number_in_year(), 60);
	ASSERT_EQUAL(Date(1, 1, 1, 29, 2, 2020).get_reverse_number_in_year(), 307);

	ASSERT_EQUAL(Date(1, 1, 1, 1, 3, 2020).get_number_in_year(), 61);
	ASSERT_EQUAL(Date(1, 1, 1, 1, 3, 2020).get_reverse_number_in_year(), 367 - 61);

	ASSERT_EQUAL(Date(1, 1, 1, 1, 12, 2019).get_number_in_year(), 335);
	ASSERT_EQUAL(Date(1, 1, 1, 1, 12, 2019).get_reverse_number_in_year(), 31);

	ASSERT_EQUAL(Date(1, 1, 1, 1, 12, 2020).get_number_in_year(), 336);
	ASSERT_EQUAL(Date(1, 1, 1, 1, 12, 2020).get_reverse_number_in_year(), 31);

	ASSERT_EQUAL(Date(1, 1, 1, 31, 12, 2019).get_number_in_year(), 365);
	ASSERT_EQUAL(Date(1, 1, 1, 31, 12, 2019).get_reverse_number_in_year(), 1);

	ASSERT_EQUAL(Date(1, 1, 1, 31, 12, 2020).get_number_in_year(), 366);
	ASSERT_EQUAL(Date(1, 1, 1, 31, 12, 2020).get_reverse_number_in_year(), 1);
}

/**
\brief tests save promote and save decrease methods from Date
*/
void TestDatePromoteDecrease() {
	{
		Date date(1, 1, 1, 1, 1, 2020);
		date.save_promote_year(20);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 1, 2040));
		date.save_decrease_year(20);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 1, 2020));
	}
	{
		Date date(1, 1, 1, 29, 2, 2020);
		date.save_promote_year(1);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 3, 2021));
	}
	{
		Date date(1, 1, 1, 29, 2, 2020);
		date.save_decrease_year(1);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 3, 2019));
	}

	{
		Date date(1, 1, 1, 1, 1, 2020);
		date.save_promote_month(5);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 6, 2020));
		date.save_decrease_month(5);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 1, 2020));
		date.save_promote_month(12);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 1, 2021));
		date.save_decrease_month(12);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 1, 2020));
		date.save_decrease_month(1);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 12, 2019));
		date.save_promote_month(1);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 1, 2020));
	}
	{
		Date date(1, 1, 1, 29, 1, 2019);
		date.save_promote_month(1);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 3, 2019));
	}
	{
		Date date(1, 1, 1, 29, 3, 2019);
		date.save_decrease_month(1);
		ASSERT_EQUAL(date, Date(1, 1, 1, 28, 2, 2019));
	}
	{
		Date date(1, 1, 1, 29, 1, 2020);
		date.save_promote_month(1);
		ASSERT_EQUAL(date, Date(1, 1, 1, 29, 2, 2020));
	}
	{
		Date date(1, 1, 1, 29, 3, 2020);
		date.save_decrease_month(1);
		ASSERT_EQUAL(date, Date(1, 1, 1, 29, 2, 2020));
	}
	{
		Date date(1, 1, 1, 29, 1, 2019);
		date.save_promote_month(1);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 3, 2019));
	}
	{
		Date date(1, 1, 1, 31, 10, 2019);
		date.save_decrease_month(1);
		ASSERT_EQUAL(date, Date(1, 1, 1, 30, 9, 2019));
	}
	{
		Date date(1, 1, 1, 31, 10, 2019);
		date.save_promote_month(1);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 11, 2019));
	}
	{
		Date date(1, 1, 1, 1, 1, 2019);
		date.save_decrease_day(1);
		ASSERT_EQUAL(date, Date(1, 1, 1, 31, 12, 2018));
		date.save_promote_day(1);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 1, 2019));
	}
	{
		Date date(1, 1, 1, 1, 1, 2019);
		date.save_promote_day(30);
		ASSERT_EQUAL(date, Date(1, 1, 1, 31, 1, 2019));
		date.save_decrease_day(30);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 1, 2019));
	}
	{
		Date date(1, 1, 1, 1, 1, 2019);
		date.save_promote_day(31);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 2, 2019));
		date.save_decrease_day(31);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 1, 2019));
	}
	{
		Date date(1, 1, 1, 1, 2, 2019);
		date.save_promote_day(28);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 3, 2019));
		date.save_decrease_day(28);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 2, 2019));
	}
	{
		Date date(1, 1, 1, 1, 2, 2019);
		date.save_promote_day(59);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 4, 2019));
		date.save_decrease_day(59);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 2, 2019));
	}
	{
		Date date(1, 1, 1, 1, 2, 2019);
		date.save_promote_day(58);
		ASSERT_EQUAL(date, Date(1, 1, 1, 31, 3, 2019));
		date.save_decrease_day(58);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 2, 2019));
	}
	{
		Date date(1, 1, 1, 1, 3, 2019);
		date.save_promote_day(31);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 4, 2019));
		date.save_decrease_day(31);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 3, 2019));
	}
	{
		Date date(1, 1, 1, 12, 6, 2019);
		date.save_promote_day(366);
		ASSERT_EQUAL(date, Date(1, 1, 1, 12, 6, 2020));
		date.save_decrease_day(366);
		ASSERT_EQUAL(date, Date(1, 1, 1, 12, 6, 2019));
	}
	{
		Date date(1, 1, 1, 12, 6, 2020);
		date.save_promote_day(365);
		ASSERT_EQUAL(date, Date(1, 1, 1, 12, 6, 2021));
		date.save_decrease_day(365);
		ASSERT_EQUAL(date, Date(1, 1, 1, 12, 6, 2020));
	}

	{
		Date date(1, 1, 0, 1, 1, 2020);
		date.save_decrease_hour(1);
		ASSERT_EQUAL(date, Date(1, 1, 23, 31, 12, 2019));
		date.save_promote_hour(1);
		ASSERT_EQUAL(date, Date(1, 1, 0, 1, 1, 2020));
	}
	{
		Date date(1, 1, 0, 1, 1, 2020);
		date.save_promote_hour(23);
		ASSERT_EQUAL(date, Date(1, 1, 23, 1, 1, 2020));
		date.save_decrease_hour(23);
		ASSERT_EQUAL(date, Date(1, 1, 0, 1, 1, 2020));
	}
	{
		Date date(1, 1, 0, 1, 1, 2020);
		date.save_promote_hour(24);
		ASSERT_EQUAL(date, Date(1, 1, 0, 2, 1, 2020));
		date.save_decrease_hour(24);
		ASSERT_EQUAL(date, Date(1, 1, 0, 1, 1, 2020));
	}
	{
		Date date(1, 1, 22, 1, 1, 2020);
		date.save_promote_hour(3);
		ASSERT_EQUAL(date, Date(1, 1, 1, 2, 1, 2020));
		date.save_decrease_hour(3);
		ASSERT_EQUAL(date, Date(1, 1,22, 1, 1, 2020));
	}
	{
		Date date(1, 1, 23, 28, 2, 2019);
		date.save_promote_hour(2);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 3, 2019));
		date.save_decrease_hour(2);
		ASSERT_EQUAL(date, Date(1, 1, 23, 28, 2, 2019));
	}
	{
		Date date(1, 1, 23, 28, 2, 2020);
		date.save_promote_hour(2);
		ASSERT_EQUAL(date, Date(1, 1, 1, 29, 2, 2020));
		date.save_decrease_hour(2);
		ASSERT_EQUAL(date, Date(1, 1, 23, 28, 2, 2020));
	}
	{
		Date date(1, 1, 23, 28, 2, 2020);
		date.save_promote_hour(26);
		ASSERT_EQUAL(date, Date(1, 1, 1, 1, 3, 2020));
		date.save_decrease_hour(26);
		ASSERT_EQUAL(date, Date(1, 1, 23, 28, 2, 2020));
	}

	{
		Date date(1, 0, 0, 1, 1, 2020);
		date.save_decrease_minute(1);
		ASSERT_EQUAL(date, Date(1, 59, 23, 31, 12, 2019));
		date.save_promote_minute(1);
		ASSERT_EQUAL(date, Date(1, 0, 0, 1, 1, 2020));
	}
	{
		Date date(1, 0, 23, 1, 1, 2020);
		date.save_promote_minute(59);
		ASSERT_EQUAL(date, Date(1, 59, 23, 1, 1, 2020));
		date.save_decrease_minute(59);
		ASSERT_EQUAL(date, Date(1, 0, 23, 1, 1, 2020));
	}
	{
		Date date(1, 0, 23, 1, 1, 2020);
		date.save_promote_minute(60);
		ASSERT_EQUAL(date, Date(1, 0, 0, 2, 1, 2020));
		date.save_promote_minute(60);
		ASSERT_EQUAL(date, Date(1, 0, 1, 2, 1, 2020));
		date.save_decrease_minute(60);
		ASSERT_EQUAL(date, Date(1, 0, 0, 2, 1, 2020));
		date.save_decrease_minute(60);
		ASSERT_EQUAL(date, Date(1, 0, 23, 1, 1, 2020));
	}
	{
		Date date(1, 58, 23, 28, 2, 2019);
		date.save_promote_minute(1);
		ASSERT_EQUAL(date, Date(1, 59, 23, 28, 2, 2019));
		date.save_promote_minute(1);
		ASSERT_EQUAL(date, Date(1, 0, 0, 1, 3, 2019));
		date.save_decrease_minute(2);
		ASSERT_EQUAL(date, Date(1, 58, 23, 28, 2, 2019));
	}
	{
		Date date(1, 58, 23, 28, 2, 2020);
		date.save_promote_minute(1);
		ASSERT_EQUAL(date, Date(1, 59, 23, 28, 2, 2020));
		date.save_promote_minute(1);
		ASSERT_EQUAL(date, Date(1, 0, 0, 29, 2, 2020));
		date.save_decrease_minute(2);
		ASSERT_EQUAL(date, Date(1, 58, 23, 28, 2, 2020));
	}
	{
		Date date(1, 58, 23, 29, 2, 2020);
		date.save_promote_minute(1);
		ASSERT_EQUAL(date, Date(1, 59, 23, 29, 2, 2020));
		date.save_promote_minute(1);
		ASSERT_EQUAL(date, Date(1, 0, 0, 1, 3, 2020));
		date.save_decrease_minute(2);
		ASSERT_EQUAL(date, Date(1, 58, 23, 29, 2, 2020));
	}

	{
		Date date(0, 0, 0, 1, 1, 2020);
		date.save_decrease_second(1);
		ASSERT_EQUAL(date, Date(59, 59, 23, 31, 12, 2019));
		date.save_promote_second(1);
		ASSERT_EQUAL(date, Date(0, 0, 0, 1, 1, 2020));
	}
	{
		Date date(0, 0, 23, 1, 1, 2020);
		date.save_promote_second(59);
		ASSERT_EQUAL(date, Date(59, 0, 23, 1, 1, 2020));
		date.save_decrease_second(59);
		ASSERT_EQUAL(date, Date(0, 0, 23, 1, 1, 2020));
	}
	{
		Date date(0, 59, 23, 1, 1, 2020);
		date.save_promote_second(59);
		ASSERT_EQUAL(date, Date(59, 59, 23, 1, 1, 2020));
		date.save_promote_second(1);
		ASSERT_EQUAL(date, Date(0, 0, 0, 2, 1, 2020));
		date.save_promote_second(60);
		ASSERT_EQUAL(date, Date(0, 1, 0, 2, 1, 2020));
		date.save_decrease_second(60);
		ASSERT_EQUAL(date, Date(0, 0, 0, 2, 1, 2020));
		date.save_decrease_second(1);
		ASSERT_EQUAL(date, Date(59, 59, 23, 1, 1, 2020));
		date.save_decrease_second(59);
		ASSERT_EQUAL(date, Date(0, 59, 23, 1, 1, 2020));
	}
	{
		Date date(58, 59, 23, 28, 2, 2019);
		date.save_promote_second(1);
		ASSERT_EQUAL(date, Date(59, 59, 23, 28, 2, 2019));
		date.save_promote_second(1);
		ASSERT_EQUAL(date, Date(0, 0, 0, 1, 3, 2019));
		date.save_decrease_second(2);
		ASSERT_EQUAL(date, Date(58, 59, 23, 28, 2, 2019));
	}
	{
		Date date(58, 59, 23, 28, 2, 2020);
		date.save_promote_second(1);
		ASSERT_EQUAL(date, Date(59, 59, 23, 28, 2, 2020));
		date.save_promote_second(1);
		ASSERT_EQUAL(date, Date(0, 0, 0, 29, 2, 2020));
		date.save_decrease_second(2);
		ASSERT_EQUAL(date, Date(58, 59, 23, 28, 2, 2020));
	}
	{
		Date date(58, 59, 23, 29, 2, 2020);
		date.save_promote_second(1);
		ASSERT_EQUAL(date, Date(59, 59, 23, 29, 2, 2020));
		date.save_promote_second(1);
		ASSERT_EQUAL(date, Date(0, 0, 0, 1, 3, 2020));
		date.save_decrease_second(2);
		ASSERT_EQUAL(date, Date(58, 59, 23, 29, 2, 2020));
	}
}

/**
\brief tests Date::difference, part1
*/
void TestDateDifference1() {
	{
		ASSERT_EQUAL(Date(59, 59, 23, 31, 12, 2019).difference(Date(0, 0, 0, 1, 1, 2020),
			MeasureTime::months), 0);
		ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2020).difference(Date(59, 59, 23, 31, 12, 2019),
			MeasureTime::months), 0);

		ASSERT_EQUAL(Date(1, 1, 1, 12, 6, 2019).difference(Date(1, 1, 1, 11, 7, 2019),
			MeasureTime::months), 0);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 6, 2019).difference(Date(1, 1, 1, 12, 7, 2019),
			MeasureTime::months), 1);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 6, 2019).difference(Date(1, 1, 1, 11, 9, 2019),
			MeasureTime::months), 2);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 6, 2019).difference(Date(1, 1, 1, 12, 9, 2019),
			MeasureTime::months), 3);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 6, 2019).difference(Date(1, 1, 1, 11, 11, 2019),
			MeasureTime::months), 4);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 6, 2019).difference(Date(1, 1, 1, 12, 11, 2019),
			MeasureTime::months), 5);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 6, 2019).difference(Date(1, 1, 1, 11,1, 2020),
			MeasureTime::months), 6);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 6, 2019).difference(Date(1, 1, 1, 12, 1, 2020),
			MeasureTime::months), 7);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 6, 2019).difference(Date(1, 1, 1, 11, 3, 2020),
			MeasureTime::months), 8);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 6, 2019).difference(Date(1, 1, 1, 12, 3, 2020),
			MeasureTime::months), 9);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 6, 2019).difference(Date(1, 1, 1, 11, 5, 2020),
			MeasureTime::months), 10);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 6, 2019).difference(Date(1, 1, 1, 12, 5, 2020),
			MeasureTime::months), 11);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 6, 2019).difference(Date(1, 1, 1, 11, 7, 2020),
			MeasureTime::months), 12);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 6, 2019).difference(Date(1, 1, 1, 12, 7, 2020),
			MeasureTime::months), 13);

		ASSERT_EQUAL(Date(1, 1, 1, 11, 7, 2019).difference(Date(1, 1, 1, 12, 6, 2019),
			MeasureTime::months), 0);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 7, 2019).difference(Date(1, 1, 1, 12, 6, 2019),
			MeasureTime::months), -1);
		ASSERT_EQUAL(Date(1, 1, 1, 11, 9, 2019).difference(Date(1, 1, 1, 12, 6, 2019),
			MeasureTime::months), -2);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 9, 2019).difference(Date(1, 1, 1, 12, 6, 2019),
			MeasureTime::months), -3);
		ASSERT_EQUAL(Date(1, 1, 1, 11, 11, 2019).difference(Date(1, 1, 1, 12, 6, 2019),
			MeasureTime::months), -4);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 11, 2019).difference(Date(1, 1, 1, 12, 6, 2019),
			MeasureTime::months), -5);
		ASSERT_EQUAL(Date(1, 1, 1, 11, 1, 2020).difference(Date(1, 1, 1, 12, 6, 2019),
			MeasureTime::months), -6);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 1, 2020).difference(Date(1, 1, 1, 12, 6, 2019),
			MeasureTime::months), -7);
		ASSERT_EQUAL(Date(1, 1, 1, 11, 3, 2020).difference(Date(1, 1, 1, 12, 6, 2019),
			MeasureTime::months), -8);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 3, 2020).difference(Date(1, 1, 1, 12, 6, 2019),
			MeasureTime::months), -9);
		ASSERT_EQUAL(Date(1, 1, 1, 11, 5, 2020).difference(Date(1, 1, 1, 12, 6, 2019),
			MeasureTime::months), -10);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 5, 2020).difference(Date(1, 1, 1, 12, 6, 2019),
			MeasureTime::months), -11);
		ASSERT_EQUAL(Date(1, 1, 1, 11, 7, 2020).difference(Date(1, 1, 1, 12, 6, 2019),
			MeasureTime::months), -12);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 7, 2020).difference(Date(1, 1, 1, 12, 6, 2019),
			MeasureTime::months), -13);
	}
}

/**
\brief tests Date::difference, part2
*/
void TestDateDifference2() {
	{
		ASSERT_EQUAL(Date(59, 59, 23, 31, 12, 2019).difference(Date(0, 0, 0, 1, 1, 2020),
			MeasureTime::years), 0);
		ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2020).difference(Date(59, 59, 23, 31, 12, 2019),
			MeasureTime::years), 0);


		ASSERT_EQUAL(Date(1, 1, 1, 12, 6, 2019).difference(Date(1, 1, 1, 11, 6, 2020),
			MeasureTime::years), 0);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 6, 2019).difference(Date(1, 1, 1, 12, 6, 2020),
			MeasureTime::years), 1);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 6, 2019).difference(Date(1, 1, 1, 11, 6, 2020),
			MeasureTime::years), 0);
		ASSERT_EQUAL(Date(1, 1, 1, 1, 1, 2000).difference(Date(1, 1, 1, 1, 1, 2100),
			MeasureTime::years), 100);
		ASSERT_EQUAL(Date(1, 1, 1, 1, 1, 2000).difference(Date(0, 1, 1, 1, 1, 2100),
			MeasureTime::years), 99);
		ASSERT_EQUAL(Date(1, 1, 1, 1, 1, 2000).difference(Date(2, 1, 1, 1, 1, 2100),
			MeasureTime::years), 100);

		ASSERT_EQUAL(Date(1, 1, 1, 11, 6, 2020).difference(Date(1, 1, 1, 12, 6, 2019),
			MeasureTime::years), 0);
		ASSERT_EQUAL(Date(1, 1, 1, 12, 6, 2020).difference(Date(1, 1, 1, 12, 6, 2019),
			MeasureTime::years), -1);
		ASSERT_EQUAL(Date(1, 1, 1, 11, 6, 2020).difference(Date(1, 1, 1, 12, 6, 2019),
			MeasureTime::years), 0);
		ASSERT_EQUAL(Date(1, 1, 1, 1, 1, 2100).difference(Date(1, 1, 1, 1, 1, 2000),
			MeasureTime::years), -100);
		ASSERT_EQUAL(Date(0, 1, 1, 1, 1, 2100).difference(Date(1, 1, 1, 1, 1, 2000),
			MeasureTime::years), -99);
		ASSERT_EQUAL(Date(2, 1, 1, 1, 1, 2100).difference(Date(1, 1, 1, 1, 1, 2000),
			MeasureTime::years), -100);
	}
	{
		ASSERT_EQUAL(Date(59, 59, 23, 31, 12, 2019).difference(Date(0, 0, 0, 1, 1, 2020),
			MeasureTime::days), 0);
		ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2020).difference(Date(59, 59, 23, 31, 12, 2019),
			MeasureTime::days), 0);

		ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2019).difference(Date(59, 59, 23, 1, 1, 2019),
			MeasureTime::days), 0);
		ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2019).difference(Date(0, 0, 0, 2, 1, 2019),
			MeasureTime::days), 1);
		ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2019).difference(Date(0, 0, 0, 1, 1, 2020),
			MeasureTime::days), 365);
		ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2020).difference(Date(0, 0, 0, 1, 1, 2021),
			MeasureTime::days), 366);
		ASSERT_EQUAL(Date(2, 0, 0, 1, 1, 2018).difference(Date(2, 0, 0, 1, 1, 2020),
			MeasureTime::days), 730);
		ASSERT_EQUAL(Date(1, 0, 0, 1, 1, 2018).difference(Date(2, 0, 0, 1, 1, 2020),
			MeasureTime::days), 730);
		ASSERT_EQUAL(Date(1, 0, 0, 1, 1, 2018).difference(Date(0, 0, 0, 1, 1, 2020),
			MeasureTime::days), 729);
		ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2018).difference(Date(59, 59, 23, 31, 12, 2019),
			MeasureTime::days), 729);
		ASSERT_EQUAL(Date(2, 0, 0, 1, 1, 2019).difference(Date(2, 0, 0, 1, 1, 2021),
			MeasureTime::days), 731);
		ASSERT_EQUAL(Date(1, 0, 0, 1, 1, 2019).difference(Date(2, 0, 0, 1, 1, 2021),
			MeasureTime::days), 731);
		ASSERT_EQUAL(Date(1, 0, 0, 1, 1, 2019).difference(Date(0, 0, 0, 1, 1, 2021),
			MeasureTime::days), 730);
		ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2019).difference(Date(0, 0, 0, 31, 12, 2020),
			MeasureTime::days), 730);
		ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2019).difference(Date(59, 59, 23, 31, 12, 2020),
			MeasureTime::days), 730);

		ASSERT_EQUAL(Date(59, 59, 23, 1, 1, 2019).difference(Date(0, 0, 0, 1, 1, 2019),
			MeasureTime::days), 0);
		ASSERT_EQUAL(Date(0, 0, 0, 2, 1, 2019).difference(Date(0, 0, 0, 1, 1, 2019),
			MeasureTime::days), -1);
		ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2020).difference(Date(0, 0, 0, 1, 1, 2019),
			MeasureTime::days), -365);
		ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2021).difference(Date(0, 0, 0, 1, 1, 2020),
			MeasureTime::days), -366);
		ASSERT_EQUAL(Date(2, 0, 0, 1, 1, 2020).difference(Date(2, 0, 0, 1, 1, 2018),
			MeasureTime::days), -730);
		ASSERT_EQUAL(Date(2, 0, 0, 1, 1, 2020).difference(Date(1, 0, 0, 1, 1, 2018),
			MeasureTime::days), -730);
		ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2020).difference(Date(1, 0, 0, 1, 1, 2018),
			MeasureTime::days), -729);
		ASSERT_EQUAL(Date(59, 59, 23, 31, 12, 2019).difference(Date(0, 0, 0, 1, 1, 2018),
			MeasureTime::days), -729);
		ASSERT_EQUAL(Date(2, 0, 0, 1, 1, 2021).difference(Date(2, 0, 0, 1, 1, 2019),
			MeasureTime::days), -731);
		ASSERT_EQUAL(Date(2, 0, 0, 1, 1, 2021).difference(Date(1, 0, 0, 1, 1, 2019),
			MeasureTime::days), -731);
		ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2021).difference(Date(1, 0, 0, 1, 1, 2019),
			MeasureTime::days), -730);
		ASSERT_EQUAL(Date(59, 59, 23, 31, 12, 2020).difference(Date(0, 0, 0, 1, 1, 2019),
			MeasureTime::days), -730);

		ASSERT_EQUAL(Date(59, 59, 23, 28, 2, 2019).difference(Date(0, 0, 0, 1, 3, 2019),
			MeasureTime::days), 0);
		ASSERT_EQUAL(Date(59, 59, 23, 28, 2, 2020).difference(Date(0, 0, 0, 1, 3, 2020),
			MeasureTime::days), 1);
		ASSERT_EQUAL(Date(0, 0, 0, 28, 2, 2019).difference(Date(0, 0, 0, 1, 3, 2019),
			MeasureTime::days), 1);
		ASSERT_EQUAL(Date(0, 0, 0, 28, 2, 2020).difference(Date(0, 0, 0, 29, 2, 2020),
			MeasureTime::days), 1);
		ASSERT_EQUAL(Date(0, 0, 0, 28, 2, 2020).difference(Date(0, 0, 0, 1, 3, 2020),
			MeasureTime::days), 2);
		ASSERT_EQUAL(Date(0, 0, 0, 29, 2, 2020).difference(Date(59, 59, 23, 29, 2, 2020),
			MeasureTime::days), 0);


		ASSERT_EQUAL(Date(59, 59, 23, 28, 2, 2019).difference(Date(0, 0, 0, 1, 3, 2019),
			MeasureTime::days), 0);
		ASSERT_EQUAL(Date(0, 0, 0, 28, 2, 2019).difference(Date(0, 0, 0, 1, 3, 2019),
			MeasureTime::days), 1);
		ASSERT_EQUAL(Date(0, 0, 0, 28, 2, 2020).difference(Date(0, 0, 0, 29, 2, 2020),
			MeasureTime::days), 1);
		ASSERT_EQUAL(Date(0, 0, 0, 28, 2, 2020).difference(Date(0, 0, 0, 1, 3, 2020),
			MeasureTime::days), 2);

		ASSERT_EQUAL(Date(59, 59, 23, 28, 2, 2020).difference(Date(0, 0, 0, 1, 3, 2020),
			MeasureTime::days), 1);
		ASSERT_EQUAL(Date(59, 59, 23, 29, 2, 2020).difference(Date(0, 0, 0, 1, 3, 2020),
			MeasureTime::days), 0);
		ASSERT_EQUAL(Date(0, 0, 0, 29, 2, 2020).difference(Date(0, 0, 0, 1, 3, 2020),
			MeasureTime::days), 1);
		ASSERT_EQUAL(Date(0, 0, 0, 28, 2, 2020).difference(Date(0, 0, 0, 1, 3, 2021),
			MeasureTime::days), 367);
		ASSERT_EQUAL(Date(0, 0, 0, 29, 2, 2020).difference(Date(0, 0, 0, 1, 3, 2021),
			MeasureTime::days), 366);
		ASSERT_EQUAL(Date(0, 0, 0, 29, 2, 2020).difference(Date(0, 0, 0, 1, 3, 2020),
			MeasureTime::days), 1);

		ASSERT_EQUAL(Date(0, 0, 0, 28, 2, 2020).difference(Date(0, 0, 0, 28, 2, 2021),
			MeasureTime::days), 366);
		ASSERT_EQUAL(Date(0, 0, 0, 29, 2, 2020).difference(Date(0, 0, 0, 28, 2, 2021),
			MeasureTime::days), 365);

		ASSERT_EQUAL(Date(0, 0, 0, 28, 2, 2019).difference(Date(0, 0, 0, 28, 2, 2020),
			MeasureTime::days), 365);
		ASSERT_EQUAL(Date(0, 0, 0, 28, 2, 2019).difference(Date(0, 0, 0, 29, 2, 2020),
			MeasureTime::days), 366);
		ASSERT_EQUAL(Date(0, 0, 0, 28, 2, 2019).difference(Date(0, 0, 0, 1, 3, 2020),
			MeasureTime::days), 367);

		ASSERT_EQUAL(Date(0, 0, 0, 1, 12, 2019).difference(Date(0, 0, 0, 1, 1, 2020),
			MeasureTime::days), 31);
		ASSERT_EQUAL(Date(0, 0, 0, 1, 12, 2020).difference(Date(0, 0, 0, 1, 1, 2021),
			MeasureTime::days), 31);

		ASSERT_EQUAL(Date(0, 0, 0, 1, 2, 2019).difference(Date(0, 0, 0, 1, 3, 2019),
			MeasureTime::days), 28);
		ASSERT_EQUAL(Date(0, 0, 0, 1, 2, 2020).difference(Date(0, 0, 0, 1, 3, 2020),
			MeasureTime::days), 29);

		ASSERT_EQUAL(Date(0, 0, 0, 1, 6, 2019).difference(Date(0, 0, 0, 1, 7, 2019),
			MeasureTime::days), 30);
		ASSERT_EQUAL(Date(0, 0, 0, 1, 6, 2020).difference(Date(0, 0, 0, 1, 7, 2020),
			MeasureTime::days), 30);

		ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2019).difference(Date(0, 0, 0, 1, 2, 2019),
			MeasureTime::days), 31);
		ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2020).difference(Date(0, 0, 0, 1, 2, 2020),
			MeasureTime::days), 31);
	}

	{
		ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2020).difference(Date(0, 0, 10, 1, 1, 2020),
			MeasureTime::hours), 10);
		ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2020).difference(Date(59, 59, 9, 1, 1, 2020),
			MeasureTime::hours), 9);
		ASSERT_EQUAL(Date(0, 0, 23, 1, 1, 2020).difference(Date(0, 0, 1, 2, 1, 2020),
			MeasureTime::hours), 2);
		ASSERT_EQUAL(Date(0, 0, 23, 1, 1, 2020).difference(Date(0, 0, 0, 2, 1, 2020),
			MeasureTime::hours), 1);
		ASSERT_EQUAL(Date(59, 59, 23, 1, 1, 2020).difference(Date(0, 0, 1, 2, 1, 2020),
			MeasureTime::hours), 1);
		ASSERT_EQUAL(Date(59, 59, 23, 1, 1, 2020).difference(Date(0, 0, 0, 2, 1, 2020),
			MeasureTime::hours), 0);

		ASSERT_EQUAL(Date(59, 59, 23, 31, 12, 2019).difference(Date(0, 0, 0, 1, 1, 2020),
			MeasureTime::hours), 0);
		ASSERT_EQUAL(Date(0, 0, 0, 31, 12, 2019).difference(Date(0, 0, 0, 1, 1, 2020),
			MeasureTime::hours), 24);
		ASSERT_EQUAL(Date(1, 0, 0, 31, 12, 2019).difference(Date(0, 0, 0, 1, 1, 2020),
			MeasureTime::hours), 23);

		ASSERT_EQUAL(Date(59, 59, 4, 1, 1, 2019).difference(Date(0, 0, 5, 1, 1, 2019),
			MeasureTime::hours), 0);
		ASSERT_EQUAL(Date(59, 59, 3, 1, 1, 2019).difference(Date(0, 0, 5, 1, 1, 2019),
			MeasureTime::hours), 1);
		ASSERT_EQUAL(Date(1, 0, 3, 1, 1, 2019).difference(Date(0, 0, 5, 1, 1, 2019),
			MeasureTime::hours), 1);
		ASSERT_EQUAL(Date(0, 0, 3, 1, 1, 2019).difference(Date(0, 0, 5, 1, 1, 2019),
			MeasureTime::hours), 2);

		ASSERT_EQUAL(Date(0, 0, 23, 28, 2, 2019).difference(Date(0, 0, 0, 1, 3, 2019),
			MeasureTime::hours), 1);
		ASSERT_EQUAL(Date(0, 0, 23, 28, 2, 2020).difference(Date(0, 0, 0, 1, 3, 2020),
			MeasureTime::hours), 25);
		ASSERT_EQUAL(Date(0, 0, 23, 29, 2, 2020).difference(Date(0, 0, 0, 1, 3, 2020),
			MeasureTime::hours), 1);
	}

	{
		ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2020).difference(Date(0, 10, 0, 1, 1, 2020),
			MeasureTime::minutes), 10);
		ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2020).difference(Date(59, 9, 0, 1, 1, 2020),
			MeasureTime::minutes), 9);
		ASSERT_EQUAL(Date(0, 59, 23, 1, 1, 2020).difference(Date(0, 1, 0, 2, 1, 2020),
			MeasureTime::minutes), 2);
		ASSERT_EQUAL(Date(0, 59, 23, 1, 1, 2020).difference(Date(0, 0, 0, 2, 1, 2020),
			MeasureTime::minutes), 1);
		ASSERT_EQUAL(Date(59, 59, 23, 1, 1, 2020).difference(Date(0, 1, 0, 2, 1, 2020),
			MeasureTime::minutes), 1);
		ASSERT_EQUAL(Date(59, 59, 23, 1, 1, 2020).difference(Date(0, 0, 0, 2, 1, 2020),
			MeasureTime::minutes), 0);

		ASSERT_EQUAL(Date(59, 59, 23, 31, 12, 2019).difference(Date(0, 0, 0, 1, 1, 2020),
			MeasureTime::minutes), 0);
		ASSERT_EQUAL(Date(0, 0, 23, 31, 12, 2019).difference(Date(0, 0, 0, 1, 1, 2020),
			MeasureTime::minutes), 60);
		ASSERT_EQUAL(Date(1, 0, 23, 31, 12, 2019).difference(Date(0, 0, 0, 1, 1, 2020),
			MeasureTime::minutes), 59);

		ASSERT_EQUAL(Date(0, 59, 23, 28, 2, 2019).difference(Date(0, 0, 0, 1, 3, 2019),
			MeasureTime::minutes), 1);
		ASSERT_EQUAL(Date(0, 59, 23, 28, 2, 2020).difference(Date(0, 0, 0, 1, 3, 2020),
			MeasureTime::minutes), 24 * 60 + 1);
		ASSERT_EQUAL(Date(0, 59, 23, 29, 2, 2020).difference(Date(0, 0, 0, 1, 3, 2020),
			MeasureTime::minutes), 1);
	}

	{
		ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2020).difference(Date(10, 0, 0, 1, 1, 2020),
			MeasureTime::seconds), 10);
		ASSERT_EQUAL(Date(59, 59, 23, 1, 1, 2020).difference(Date(1, 0, 0, 2, 1, 2020),
			MeasureTime::seconds), 2);
		ASSERT_EQUAL(Date(59, 59, 23, 1, 1, 2020).difference(Date(0, 0, 0, 2, 1, 2020),
			MeasureTime::seconds), 1);

		ASSERT_EQUAL(Date(59, 59, 23, 31, 12, 2019).difference(Date(0, 0, 0, 1, 1, 2020),
			MeasureTime::seconds), 1);
		ASSERT_EQUAL(Date(0, 59, 23, 31, 12, 2019).difference(Date(0, 0, 0, 1, 1, 2020),
			MeasureTime::seconds), 60);
		ASSERT_EQUAL(Date(1, 59, 23, 31, 12, 2019).difference(Date(0, 0, 0, 1, 1, 2020),
			MeasureTime::seconds), 59);

		ASSERT_EQUAL(Date(59, 59, 23, 28, 2, 2019).difference(Date(0, 0, 0, 1, 3, 2019),
			MeasureTime::seconds), 1);
		ASSERT_EQUAL(Date(59, 59, 23, 28, 2, 2020).difference(Date(0, 0, 0, 1, 3, 2020),
			MeasureTime::seconds), 24 * 3600 + 1);
		ASSERT_EQUAL(Date(59, 59, 23, 29, 2, 2020).difference(Date(0, 0, 0, 1, 3, 2020),
			MeasureTime::seconds), 1);
	}
}

/**
\brief tests Date::get_day_of_week
*/
void TestDateDayOfWeek() {
	ASSERT_EQUAL(Date(1, 1, 1, 29, 9, 2020).get_day_of_week(), Day::Tuesday);
	ASSERT_EQUAL(Date(1, 1, 1, 3, 6, 2020).get_day_of_week(), Day::Wednesday);
	ASSERT_EQUAL(Date(1, 1, 1, 11, 3, 2021).get_day_of_week(), Day::Thursday);
	ASSERT_EQUAL(Date(1, 1, 1, 27, 9, 2020).get_day_of_week(), Day::Sunday);
	ASSERT_EQUAL(Date(1, 1, 1, 28, 2, 2021).get_day_of_week(), Day::Sunday);
	ASSERT_EQUAL(Date(1, 1, 1, 1, 3, 2021).get_day_of_week(), Day::Monday);
	ASSERT_EQUAL(Date(1, 1, 1, 28, 2, 2020).get_day_of_week(), Day::Friday);
	ASSERT_EQUAL(Date(1, 1, 1, 29, 2, 2020).get_day_of_week(), Day::Saturday);
	ASSERT_EQUAL(Date(1, 1, 1, 1, 3, 2020).get_day_of_week(), Day::Sunday);
	ASSERT_EQUAL(Date(1, 1, 1, 12, 6, 2021).get_day_of_week(), Day::Saturday);
	ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2021).get_day_of_week(), Day::Friday);

	ASSERT_EQUAL(Date(0, 0, 0, 29, 9, 2020).get_day_of_week(), Day::Tuesday);
	ASSERT_EQUAL(Date(0, 0, 0, 3, 6, 2020).get_day_of_week(), Day::Wednesday);
	ASSERT_EQUAL(Date(0, 0, 0, 11, 3, 2021).get_day_of_week(), Day::Thursday);
	ASSERT_EQUAL(Date(0, 0, 0, 27, 9, 2020).get_day_of_week(), Day::Sunday);
	ASSERT_EQUAL(Date(0, 0, 0, 28, 2, 2021).get_day_of_week(), Day::Sunday);
	ASSERT_EQUAL(Date(0, 0, 0, 1, 3, 2021).get_day_of_week(), Day::Monday);
	ASSERT_EQUAL(Date(0, 0, 0, 28, 2, 2020).get_day_of_week(), Day::Friday);
	ASSERT_EQUAL(Date(0, 0, 0, 29, 2, 2020).get_day_of_week(), Day::Saturday);
	ASSERT_EQUAL(Date(0, 0, 0, 1, 3, 2020).get_day_of_week(), Day::Sunday);
	ASSERT_EQUAL(Date(0, 0, 0, 12, 6, 2021).get_day_of_week(), Day::Saturday);
	ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2021).get_day_of_week(), Day::Friday);

	ASSERT_EQUAL(Date(59, 59, 23, 29, 9, 2020).get_day_of_week(), Day::Tuesday);
	ASSERT_EQUAL(Date(59, 59, 23, 3, 6, 2020).get_day_of_week(), Day::Wednesday);
	ASSERT_EQUAL(Date(59, 59, 23, 11, 3, 2021).get_day_of_week(), Day::Thursday);
	ASSERT_EQUAL(Date(59, 59, 23, 27, 9, 2020).get_day_of_week(), Day::Sunday);
	ASSERT_EQUAL(Date(59, 59, 23, 28, 2, 2021).get_day_of_week(), Day::Sunday);
	ASSERT_EQUAL(Date(59, 59, 23, 1, 3, 2021).get_day_of_week(), Day::Monday);
	ASSERT_EQUAL(Date(59, 59, 23, 28, 2, 2020).get_day_of_week(), Day::Friday);
	ASSERT_EQUAL(Date(59, 59, 23, 29, 2, 2020).get_day_of_week(), Day::Saturday);
	ASSERT_EQUAL(Date(59, 59, 23, 1, 3, 2020).get_day_of_week(), Day::Sunday);
	ASSERT_EQUAL(Date(59, 59, 23, 12, 6, 2021).get_day_of_week(), Day::Saturday);
	ASSERT_EQUAL(Date(59, 59, 23, 1, 1, 2021).get_day_of_week(), Day::Friday);
}

/**
\brief tests alternative constructor for Date
*/
void TestDateAlternativeConstructor() {
	ASSERT_EQUAL(Date(1, 1, 1, 30, 9, 2020), Date(1, 1, 1, Day::Wednesday, 1, 0, 9, 2020));
	ASSERT_EQUAL(Date(1, 1, 1, 30, 9, 2020), Date(1, 1, 1, Day::Thursday, 0, 0, 9, 2020));
	ASSERT_EQUAL(Date(1, 1, 1, 30, 9, 2020), Date(1, 1, 1, Day::Wednesday, 1, 0, 9, 2020));
	ASSERT_EQUAL(Date(1, 1, 1, 30, 9, 2020), Date(1, 1, 1, Day::Wednesday, 5, 1, 9, 2020));
	ASSERT_EQUAL(Date(1, 1, 1, 1, 9, 2020), Date(1, 1, 1, Day::Wednesday, 0, 1, 9, 2020));
	ASSERT_EQUAL(Date(1, 1, 1, 28, 2, 2021), Date(1, 1, 1, Day::Sunday, 1, 0, 2, 2021));
	ASSERT_EQUAL(Date(1, 1, 1, 27, 2, 2021), Date(1, 1, 1, Day::Saturday, 1, 0, 2, 2021));
	ASSERT_EQUAL(Date(1, 1, 1, 29, 2, 2020), Date(1, 1, 1, Day::Saturday, 1, 0, 2, 2020));
	ASSERT_EQUAL(Date(1, 1, 1, 28, 2, 2020), Date(1, 1, 1, Day::Friday, 1, 0, 2, 2020));
	ASSERT_EQUAL(Date(1, 1, 1, 12, 6, 2021), Date(1, 1, 1, Day::Saturday, 2, 1, 6, 2021));
	ASSERT_EQUAL(Date(1, 1, 1, 12, 6, 2021), Date(1, 1, 1, Day::Saturday, 3, 0, 6, 2021));
}

/**
\brief tests Date::get_number_of_week
*/
void TestDateNumberOfWeek() {
	ASSERT_EQUAL(Date(1, 1, 1, 1, 9, 2020).get_number_of_week(1), 0);
	ASSERT_EQUAL(Date(1, 1, 1, 2, 9, 2020).get_number_of_week(1), 0);
	ASSERT_EQUAL(Date(1, 1, 1, 3, 9, 2020).get_number_of_week(1), 0);
	ASSERT_EQUAL(Date(1, 1, 1, 4, 9, 2020).get_number_of_week(1), 0);
	ASSERT_EQUAL(Date(1, 1, 1, 5, 9, 2020).get_number_of_week(1), 0);
	ASSERT_EQUAL(Date(1, 1, 1, 6, 9, 2020).get_number_of_week(1), 0);
	ASSERT_EQUAL(Date(1, 1, 1, 7, 9, 2020).get_number_of_week(1), 1);
	ASSERT_EQUAL(Date(1, 1, 1, 30, 9, 2020).get_number_of_week(1), 4);
	ASSERT_EQUAL(Date(1, 1, 1, 12, 6, 2021).get_number_of_week(1), 1);

	ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2021).get_number_of_week(0), 0);
	ASSERT_EQUAL(Date(0, 0, 0, 2, 1, 2021).get_number_of_week(0), 0);
	ASSERT_EQUAL(Date(0, 0, 0, 3, 1, 2021).get_number_of_week(0), 0);
	ASSERT_EQUAL(Date(0, 0, 0, 4, 1, 2021).get_number_of_week(0), 1);
	ASSERT_EQUAL(Date(0, 0, 0, 5, 1, 2021).get_number_of_week(0), 1);
	ASSERT_EQUAL(Date(0, 0, 0, 6, 1, 2021).get_number_of_week(0), 1);
	ASSERT_EQUAL(Date(0, 0, 0, 7, 1, 2021).get_number_of_week(0), 1);
	ASSERT_EQUAL(Date(0, 0, 0, 8, 1, 2021).get_number_of_week(0), 1);
	ASSERT_EQUAL(Date(0, 0, 0, 9, 1, 2021).get_number_of_week(0), 1);
	ASSERT_EQUAL(Date(0, 0, 0, 10, 1, 2021).get_number_of_week(0), 1);
	ASSERT_EQUAL(Date(0, 0, 0, 11, 1, 2021).get_number_of_week(0), 2);

	ASSERT_EQUAL(Date(0, 0, 0, 12, 6, 2020).get_number_of_week(0), 23);
	ASSERT_EQUAL(Date(59, 59, 23, 12, 6, 2020).get_number_of_week(0), 23);

	ASSERT_EQUAL(Date(59, 59, 23, 14, 6, 2020).get_number_of_week(0), 23);
	ASSERT_EQUAL(Date(0, 0, 0, 15, 6, 2020).get_number_of_week(0), 24);

	ASSERT_EQUAL(Date(59, 59, 23, 31, 12, 2020).get_number_of_week(0), 52);
	ASSERT_EQUAL(Date(0, 0, 0, 1, 1, 2021).get_number_of_week(0), 0);
}

/**
\brief statistics functions (for years and ranges of Dates)
*/
void TestDateStatistics() {
	ASSERT_EQUAL(statistics(Date(59, 59, 23, 11, 6, 2019),
		Date(0, 0, 0, 1, 1, 2020), 12), Day::Thursday);
	ASSERT_EQUAL(statistics(2020,1), Day::Wednesday);
	ASSERT_EQUAL(statistics(Date(0, 0, 0, 30, 9, 2020),
		Date(0, 0, 0, 30, 9, 2020), 12), Day::Monday);
	ASSERT_EQUAL(statistics(Date(0, 0, 0, 30, 9, 2020),
		Date(59, 59, 23, 30, 9, 2020), 12), Day::Monday);
	ASSERT_EQUAL(statistics(Date(0, 0, 0, 30, 9, 2019),
		Date(59, 59, 23, 30, 9, 2020), 12), Day::Sunday);
	ASSERT_EQUAL(statistics(Date(0, 0, 0, 30, 9, 2020),
		Date(59, 59, 23, 30, 9, 2020), 30), Day::Wednesday);
	ASSERT_EQUAL(statistics(Date(0, 0, 0, 30, 9, 2020),
		Date(0, 0, 0, 1, 10, 2020), 30), Day::Wednesday);
	ASSERT_EQUAL(statistics(Date(59, 59, 23, 30, 9, 2020),
		Date(59, 59, 23, 30, 10, 2020), 1), Day::Thursday);
	ASSERT_EQUAL(statistics(2020, 1), Day::Wednesday);
	ASSERT_EQUAL(statistics(2019, 20), Day::Wednesday);
	ASSERT_EQUAL(statistics(2019, 29), Day::Monday);
	ASSERT_EQUAL(statistics(2020, 29), Day::Wednesday);
	ASSERT_EQUAL(statistics(2021, 31), Day::Sunday);
}

/**
\brief launches tests for Date
*/
void TestDate() {
	TestDateBasic();
	TestDateLeap();
	TestDateIsValid();
	TestDateNumberInYear();
	TestDatePromoteDecrease();
	TestDateDifference1();
	TestDateDifference2();
	TestDateDayOfWeek();
	TestDateAlternativeConstructor();
	TestDateNumberOfWeek();
	TestDateStatistics();
}

/**
\brief tests basic methods of graphs (add_node, get_node, add_edge, get_edge, delete_node, delete_edge)

\param graph reference to some graph (AdjacencyMatrix or AdjacencyStructure in tests)
*/
template <typename NodeType, typename EdgeType>
void TestBasic(Graph<NodeType, EdgeType>& graph) {
	NodeType new_node = random_element(NodeType());
	size_t pos = graph.add_node(new_node);
	ASSERT_EQUAL(graph.get_node(pos), new_node);
	ASSERT_EQUAL(graph.delete_node(pos), new_node);

	NodeType Node1 = random_element(NodeType());
	size_t pos1 = graph.add_node(Node1);
	NodeType Node2 = random_element(NodeType());
	size_t pos2 = graph.add_node(Node2);
	NodeType Node3 = random_element(NodeType());
	size_t pos3 = graph.add_node(Node3);
	NodeType Node4 = random_element(NodeType());
	size_t pos4 = graph.add_node(Node4);

	ASSERT_EQUAL(graph.get_node(pos1), Node1);
	ASSERT_EQUAL(graph.get_node(pos2), Node2);
	ASSERT_EQUAL(graph.get_node(pos3), Node3);
	ASSERT_EQUAL(graph.get_node(pos4), Node4);

	EdgeType edge1 = random_element(EdgeType());
	graph.add_edge(pos1, pos2, edge1);
	EdgeType edge2 = random_element(EdgeType());
	graph.add_edge(pos1, pos3, edge2);
	EdgeType edge3 = random_element(EdgeType());
	graph.add_edge(pos2, pos4, edge3);

	ASSERT_EQUAL(graph.get_edge(pos1, pos2), edge1);
	ASSERT_EQUAL(graph.get_edge(pos1, pos3), edge2);
	ASSERT_EQUAL(graph.get_edge(pos2, pos4), edge3);

	ASSERT_EQUAL(graph.delete_edge(pos1, pos3), edge2);
	ASSERT_EQUAL(graph.get_edge(pos1, pos2), edge1);
	ASSERT_EQUAL(graph.get_edge(pos2, pos4), edge3);

	graph.delete_node(pos2);
	pos3--;
	pos4--;
	ASSERT_EQUAL(graph.get_node(pos1), Node1);
	ASSERT_EQUAL(graph.get_node(pos3), Node3);
	ASSERT_EQUAL(graph.get_node(pos4), Node4);
	graph.clear();
}

/**
\brief tests is_connected, is_acyclic, is_tree and find_components methods of graph

\param graph reference to some graph (AdjacencyMatrix or AdjacencyStructure in tests)
*/
template <typename NodeType, typename EdgeType>
void TestConnectedComponentsAcyclicTree(Graph<NodeType, EdgeType>& graph) {
	ASSERT(!graph.is_connected_graph());
	ASSERT(graph.is_acyclic());
	ASSERT(!graph.is_tree());
	ASSERT_EQUAL(std::vector<std::vector<size_t>>{}, graph.find_components());
	NodeType Node1 = random_element(NodeType());
	auto pos1 = graph.add_node(Node1);
	ASSERT(graph.is_connected_graph());
	ASSERT(graph.is_acyclic());
	ASSERT(graph.is_tree());
	ASSERT_EQUAL(std::vector<std::vector<size_t>>{ {pos1}}, graph.find_components());
	NodeType Node2 = random_element(NodeType());
	auto pos2 = graph.add_node(Node2);
	NodeType Node3 = random_element(NodeType());
	auto pos3 = graph.add_node(Node3);
	NodeType Node4 = random_element(NodeType());
	auto pos4 = graph.add_node(Node4);
	ASSERT(!graph.is_connected_graph());
	ASSERT(graph.is_acyclic());
	ASSERT(!graph.is_tree());
	std::vector<std::vector<size_t>> v{ {pos1},
		{ pos2 },
		{ pos3 },
		{ pos4 }
	};
	ASSERT_EQUAL(v, graph.find_components());

	EdgeType edge1 = random_element(EdgeType());
	graph.add_edge(pos1, pos2, edge1);
	ASSERT(!graph.is_connected_graph());
	ASSERT(graph.is_acyclic());
	ASSERT(!graph.is_tree());
	v = { {pos1,pos2},
		{ pos3 },
		{ pos4 }
	};
	ASSERT_EQUAL(v, graph.find_components());
	EdgeType edge2 = random_element(EdgeType());
	graph.add_edge(pos1, pos3, edge2);
	ASSERT(!graph.is_connected_graph());
	ASSERT(graph.is_acyclic());
	ASSERT(!graph.is_tree());
	v = { {pos1,pos2,pos3},
		{ pos4 }
	};
	ASSERT_EQUAL(v, graph.find_components());
	EdgeType edge3 = random_element(EdgeType());
	graph.add_edge(pos2, pos3, edge3);
	ASSERT(!graph.is_connected_graph());
	ASSERT(!graph.is_acyclic());
	ASSERT(!graph.is_tree());
	ASSERT_EQUAL(v, graph.find_components());
	graph.add_edge(pos2, pos4, edge3);
	ASSERT(graph.is_connected_graph());
	ASSERT(!graph.is_acyclic());
	ASSERT(!graph.is_tree());
	v = { {pos1,pos2,pos3,pos4}	};
	ASSERT_EQUAL(v, graph.find_components());
	graph.add_edge(pos3, pos4, edge1);
	ASSERT(graph.is_connected_graph());
	ASSERT(!graph.is_acyclic());
	ASSERT(!graph.is_tree());
	ASSERT_EQUAL(v, graph.find_components());

	graph.delete_edge(pos2, pos3);
	ASSERT(graph.is_connected_graph());
	ASSERT(!graph.is_acyclic());
	ASSERT(!graph.is_tree());
	v = { {pos1,pos2,pos4,pos3} };
	ASSERT_EQUAL(v, graph.find_components());

	graph.delete_edge(pos1, pos3);
	ASSERT(graph.is_connected_graph());
	ASSERT(graph.is_acyclic());
	ASSERT(graph.is_tree());
	ASSERT_EQUAL(v, graph.find_components());

	graph.delete_edge(pos2, pos4);
	v = { {pos1,pos2},{pos3,pos4} };
	ASSERT(!graph.is_connected_graph());
	ASSERT(graph.is_acyclic());
	ASSERT(!graph.is_tree());
	ASSERT_EQUAL(v, graph.find_components());

	graph.add_edge(pos2, pos3, edge3);
	ASSERT(graph.is_connected_graph());
	ASSERT(graph.is_acyclic());
	ASSERT(graph.is_tree());
	v = { {pos1,pos2,pos3,pos4} };
	ASSERT_EQUAL(v, graph.find_components());

	graph.clear();
}

/**
\brief tests dijkstra_algorithm method for AdjacencyMatrix<double, int>
*/
void TestWays1() {
	{
		AdjacencyMatrix<double, int>graph(0, 10000);
		double Node1 = random_element(double());
		size_t pos1 = graph.add_node(Node1);
		double Node2 = random_element(double());
		size_t pos2 = graph.add_node(Node2);
		double Node3 = random_element(double());
		size_t pos3 = graph.add_node(Node3);
		double Node4 = random_element(double());
		size_t pos4 = graph.add_node(Node4);
		double Node5 = random_element(double());
		size_t pos5 = graph.add_node(Node5);
		double Node6 = random_element(double());
		size_t pos6 = graph.add_node(Node6);
		double Node7 = random_element(double());
		size_t pos7 = graph.add_node(Node7);
		double Node8 = random_element(double());
		size_t pos8 = graph.add_node(Node8);
		double Node9 = random_element(double());
		size_t pos9 = graph.add_node(Node9);
		double Node10 = random_element(double());
		size_t pos10 = graph.add_node(Node10);
		auto ways = graph.dijkstra_algorithm(pos5);
		for (size_t i = pos1; i < pos10; i++) {
			if (i != pos5) {
				ASSERT_EQUAL(ways[i], 10000);
			}
		}
		ASSERT_EQUAL(ways[pos5], 0);

		graph.add_edge(pos1, pos10, 20);
		graph.add_edge(pos1, pos7, 30);

		graph.add_edge(pos2, pos9, 100);
		graph.add_edge(pos2, pos7, 10);

		graph.add_edge(pos3, pos5, 50);
		graph.add_edge(pos3, pos10, 305);

		graph.add_edge(pos4, pos7, 20);
		graph.add_edge(pos4, pos10, 16);

		graph.add_edge(pos5, pos8, 1);

		graph.add_edge(pos8, pos9, 8);

		for (size_t i = pos1; i <= pos10; i++) {
			if (i != pos6) {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos6], 10000);
			}
			else {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos6], 0);
			}
		}

		graph.add_edge(pos1, pos6, 60);
		graph.add_edge(pos3, pos6, 31);

		{
			auto ways = graph.dijkstra_algorithm(pos1);

			ASSERT_EQUAL(ways[pos1], 0);
			ASSERT_EQUAL(ways[pos2], 40);
			ASSERT_EQUAL(ways[pos3], 91);
			ASSERT_EQUAL(ways[pos4], 36);
			ASSERT_EQUAL(ways[pos5], 141);
			ASSERT_EQUAL(ways[pos6], 60);
			ASSERT_EQUAL(ways[pos7], 30);
			ASSERT_EQUAL(ways[pos8], 142);
			ASSERT_EQUAL(ways[pos9], 140);
			ASSERT_EQUAL(ways[pos10], 20);
		}
		{
			auto ways = graph.dijkstra_algorithm(pos2);

			ASSERT_EQUAL(ways[pos1], 40);
			ASSERT_EQUAL(ways[pos2], 0);
			ASSERT_EQUAL(ways[pos3], 131);
			ASSERT_EQUAL(ways[pos4], 30);
			ASSERT_EQUAL(ways[pos5], 109);
			ASSERT_EQUAL(ways[pos6], 100);
			ASSERT_EQUAL(ways[pos7], 10);
			ASSERT_EQUAL(ways[pos8], 108);
			ASSERT_EQUAL(ways[pos9], 100);
			ASSERT_EQUAL(ways[pos10], 46);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos3);

			ASSERT_EQUAL(ways[pos1], 91);
			ASSERT_EQUAL(ways[pos2], 131);
			ASSERT_EQUAL(ways[pos3], 0);
			ASSERT_EQUAL(ways[pos4], 127);
			ASSERT_EQUAL(ways[pos5], 50);
			ASSERT_EQUAL(ways[pos6], 31);
			ASSERT_EQUAL(ways[pos7], 121);
			ASSERT_EQUAL(ways[pos8], 51);
			ASSERT_EQUAL(ways[pos9], 59);
			ASSERT_EQUAL(ways[pos10], 111);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos4);

			ASSERT_EQUAL(ways[pos1], 36);
			ASSERT_EQUAL(ways[pos2], 30);
			ASSERT_EQUAL(ways[pos3], 127);
			ASSERT_EQUAL(ways[pos4], 0);
			ASSERT_EQUAL(ways[pos5], 139);
			ASSERT_EQUAL(ways[pos6], 96);
			ASSERT_EQUAL(ways[pos7], 20);
			ASSERT_EQUAL(ways[pos8], 138);
			ASSERT_EQUAL(ways[pos9], 130);
			ASSERT_EQUAL(ways[pos10], 16);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos5);

			ASSERT_EQUAL(ways[pos1], 141);
			ASSERT_EQUAL(ways[pos2], 109);
			ASSERT_EQUAL(ways[pos3], 50);
			ASSERT_EQUAL(ways[pos4], 139);
			ASSERT_EQUAL(ways[pos5], 0);
			ASSERT_EQUAL(ways[pos6], 81);
			ASSERT_EQUAL(ways[pos7], 119);
			ASSERT_EQUAL(ways[pos8], 1);
			ASSERT_EQUAL(ways[pos9], 9);
			ASSERT_EQUAL(ways[pos10], 155);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos6);

			ASSERT_EQUAL(ways[pos1], 60);
			ASSERT_EQUAL(ways[pos2], 100);
			ASSERT_EQUAL(ways[pos3], 31);
			ASSERT_EQUAL(ways[pos4], 96);
			ASSERT_EQUAL(ways[pos5], 81);
			ASSERT_EQUAL(ways[pos6], 0);
			ASSERT_EQUAL(ways[pos7], 90);
			ASSERT_EQUAL(ways[pos8], 82);
			ASSERT_EQUAL(ways[pos9], 90);
			ASSERT_EQUAL(ways[pos10], 80);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos7);

			ASSERT_EQUAL(ways[pos1], 30);
			ASSERT_EQUAL(ways[pos2], 10);
			ASSERT_EQUAL(ways[pos3], 121);
			ASSERT_EQUAL(ways[pos4], 20);
			ASSERT_EQUAL(ways[pos5], 119);
			ASSERT_EQUAL(ways[pos6], 90);
			ASSERT_EQUAL(ways[pos7], 0);
			ASSERT_EQUAL(ways[pos8], 118);
			ASSERT_EQUAL(ways[pos9], 110);
			ASSERT_EQUAL(ways[pos10], 36);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos8);

			ASSERT_EQUAL(ways[pos1], 142);
			ASSERT_EQUAL(ways[pos2], 108);
			ASSERT_EQUAL(ways[pos3], 51);
			ASSERT_EQUAL(ways[pos4], 138);
			ASSERT_EQUAL(ways[pos5], 1);
			ASSERT_EQUAL(ways[pos6], 82);
			ASSERT_EQUAL(ways[pos7], 118);
			ASSERT_EQUAL(ways[pos8], 0);
			ASSERT_EQUAL(ways[pos9], 8);
			ASSERT_EQUAL(ways[pos10], 154);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos9);

			ASSERT_EQUAL(ways[pos1], 140);
			ASSERT_EQUAL(ways[pos2], 100);
			ASSERT_EQUAL(ways[pos3], 59);
			ASSERT_EQUAL(ways[pos4], 130);
			ASSERT_EQUAL(ways[pos5], 9);
			ASSERT_EQUAL(ways[pos6], 90);
			ASSERT_EQUAL(ways[pos7], 110);
			ASSERT_EQUAL(ways[pos8], 8);
			ASSERT_EQUAL(ways[pos9], 0);
			ASSERT_EQUAL(ways[pos10], 146);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos10);

			ASSERT_EQUAL(ways[pos1], 20);
			ASSERT_EQUAL(ways[pos2], 46);
			ASSERT_EQUAL(ways[pos3], 111);
			ASSERT_EQUAL(ways[pos4], 16);
			ASSERT_EQUAL(ways[pos5], 155);
			ASSERT_EQUAL(ways[pos6], 80);
			ASSERT_EQUAL(ways[pos7], 36);
			ASSERT_EQUAL(ways[pos8], 154);
			ASSERT_EQUAL(ways[pos9], 146);
			ASSERT_EQUAL(ways[pos10], 0);
		}
	}
}


/**
\brief tests dijkstra_algorithm method for AdjacencyStructure<double, int>
*/
void TestWays2() {
	{
		AdjacencyStructure<double, int>graph(0, 10000);
		double Node1 = random_element(double());
		size_t pos1 = graph.add_node(Node1);
		double Node2 = random_element(double());
		size_t pos2 = graph.add_node(Node2);
		double Node3 = random_element(double());
		size_t pos3 = graph.add_node(Node3);
		double Node4 = random_element(double());
		size_t pos4 = graph.add_node(Node4);
		double Node5 = random_element(double());
		size_t pos5 = graph.add_node(Node5);
		double Node6 = random_element(double());
		size_t pos6 = graph.add_node(Node6);
		double Node7 = random_element(double());
		size_t pos7 = graph.add_node(Node7);
		double Node8 = random_element(double());
		size_t pos8 = graph.add_node(Node8);
		double Node9 = random_element(double());
		size_t pos9 = graph.add_node(Node9);
		double Node10 = random_element(double());
		size_t pos10 = graph.add_node(Node10);
		auto ways = graph.dijkstra_algorithm(pos5);
		for (size_t i = pos1; i < pos10; i++) {
			if (i != pos5) {
				ASSERT_EQUAL(ways[i], 10000);
			}
		}
		ASSERT_EQUAL(ways[pos5], 0);

		graph.add_edge(pos1, pos10, 20);
		graph.add_edge(pos1, pos7, 30);

		graph.add_edge(pos2, pos9, 100);
		graph.add_edge(pos2, pos7, 10);

		graph.add_edge(pos3, pos5, 50);
		graph.add_edge(pos3, pos10, 305);

		graph.add_edge(pos4, pos7, 20);
		graph.add_edge(pos4, pos10, 16);

		graph.add_edge(pos5, pos8, 1);

		graph.add_edge(pos8, pos9, 8);

		for (size_t i = pos1; i <= pos10; i++) {
			if (i != pos6) {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos6], 10000);
			}
			else {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos6], 0);
			}
		}

		graph.add_edge(pos1, pos6, 60);
		graph.add_edge(pos3, pos6, 31);

		{
			auto ways = graph.dijkstra_algorithm(pos1);

			ASSERT_EQUAL(ways[pos1], 0);
			ASSERT_EQUAL(ways[pos2], 40);
			ASSERT_EQUAL(ways[pos3], 91);
			ASSERT_EQUAL(ways[pos4], 36);
			ASSERT_EQUAL(ways[pos5], 141);
			ASSERT_EQUAL(ways[pos6], 60);
			ASSERT_EQUAL(ways[pos7], 30);
			ASSERT_EQUAL(ways[pos8], 142);
			ASSERT_EQUAL(ways[pos9], 140);
			ASSERT_EQUAL(ways[pos10], 20);
		}
		{
			auto ways = graph.dijkstra_algorithm(pos2);

			ASSERT_EQUAL(ways[pos1], 40);
			ASSERT_EQUAL(ways[pos2], 0);
			ASSERT_EQUAL(ways[pos3], 131);
			ASSERT_EQUAL(ways[pos4], 30);
			ASSERT_EQUAL(ways[pos5], 109);
			ASSERT_EQUAL(ways[pos6], 100);
			ASSERT_EQUAL(ways[pos7], 10);
			ASSERT_EQUAL(ways[pos8], 108);
			ASSERT_EQUAL(ways[pos9], 100);
			ASSERT_EQUAL(ways[pos10], 46);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos3);

			ASSERT_EQUAL(ways[pos1], 91);
			ASSERT_EQUAL(ways[pos2], 131);
			ASSERT_EQUAL(ways[pos3], 0);
			ASSERT_EQUAL(ways[pos4], 127);
			ASSERT_EQUAL(ways[pos5], 50);
			ASSERT_EQUAL(ways[pos6], 31);
			ASSERT_EQUAL(ways[pos7], 121);
			ASSERT_EQUAL(ways[pos8], 51);
			ASSERT_EQUAL(ways[pos9], 59);
			ASSERT_EQUAL(ways[pos10], 111);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos4);

			ASSERT_EQUAL(ways[pos1], 36);
			ASSERT_EQUAL(ways[pos2], 30);
			ASSERT_EQUAL(ways[pos3], 127);
			ASSERT_EQUAL(ways[pos4], 0);
			ASSERT_EQUAL(ways[pos5], 139);
			ASSERT_EQUAL(ways[pos6], 96);
			ASSERT_EQUAL(ways[pos7], 20);
			ASSERT_EQUAL(ways[pos8], 138);
			ASSERT_EQUAL(ways[pos9], 130);
			ASSERT_EQUAL(ways[pos10], 16);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos5);

			ASSERT_EQUAL(ways[pos1], 141);
			ASSERT_EQUAL(ways[pos2], 109);
			ASSERT_EQUAL(ways[pos3], 50);
			ASSERT_EQUAL(ways[pos4], 139);
			ASSERT_EQUAL(ways[pos5], 0);
			ASSERT_EQUAL(ways[pos6], 81);
			ASSERT_EQUAL(ways[pos7], 119);
			ASSERT_EQUAL(ways[pos8], 1);
			ASSERT_EQUAL(ways[pos9], 9);
			ASSERT_EQUAL(ways[pos10], 155);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos6);

			ASSERT_EQUAL(ways[pos1], 60);
			ASSERT_EQUAL(ways[pos2], 100);
			ASSERT_EQUAL(ways[pos3], 31);
			ASSERT_EQUAL(ways[pos4], 96);
			ASSERT_EQUAL(ways[pos5], 81);
			ASSERT_EQUAL(ways[pos6], 0);
			ASSERT_EQUAL(ways[pos7], 90);
			ASSERT_EQUAL(ways[pos8], 82);
			ASSERT_EQUAL(ways[pos9], 90);
			ASSERT_EQUAL(ways[pos10], 80);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos7);

			ASSERT_EQUAL(ways[pos1], 30);
			ASSERT_EQUAL(ways[pos2], 10);
			ASSERT_EQUAL(ways[pos3], 121);
			ASSERT_EQUAL(ways[pos4], 20);
			ASSERT_EQUAL(ways[pos5], 119);
			ASSERT_EQUAL(ways[pos6], 90);
			ASSERT_EQUAL(ways[pos7], 0);
			ASSERT_EQUAL(ways[pos8], 118);
			ASSERT_EQUAL(ways[pos9], 110);
			ASSERT_EQUAL(ways[pos10], 36);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos8);

			ASSERT_EQUAL(ways[pos1], 142);
			ASSERT_EQUAL(ways[pos2], 108);
			ASSERT_EQUAL(ways[pos3], 51);
			ASSERT_EQUAL(ways[pos4], 138);
			ASSERT_EQUAL(ways[pos5], 1);
			ASSERT_EQUAL(ways[pos6], 82);
			ASSERT_EQUAL(ways[pos7], 118);
			ASSERT_EQUAL(ways[pos8], 0);
			ASSERT_EQUAL(ways[pos9], 8);
			ASSERT_EQUAL(ways[pos10], 154);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos9);

			ASSERT_EQUAL(ways[pos1], 140);
			ASSERT_EQUAL(ways[pos2], 100);
			ASSERT_EQUAL(ways[pos3], 59);
			ASSERT_EQUAL(ways[pos4], 130);
			ASSERT_EQUAL(ways[pos5], 9);
			ASSERT_EQUAL(ways[pos6], 90);
			ASSERT_EQUAL(ways[pos7], 110);
			ASSERT_EQUAL(ways[pos8], 8);
			ASSERT_EQUAL(ways[pos9], 0);
			ASSERT_EQUAL(ways[pos10], 146);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos10);

			ASSERT_EQUAL(ways[pos1], 20);
			ASSERT_EQUAL(ways[pos2], 46);
			ASSERT_EQUAL(ways[pos3], 111);
			ASSERT_EQUAL(ways[pos4], 16);
			ASSERT_EQUAL(ways[pos5], 155);
			ASSERT_EQUAL(ways[pos6], 80);
			ASSERT_EQUAL(ways[pos7], 36);
			ASSERT_EQUAL(ways[pos8], 154);
			ASSERT_EQUAL(ways[pos9], 146);
			ASSERT_EQUAL(ways[pos10], 0);
		}
	}
}

/**
\brief tests dijkstra_algorithm method for AdjacencyMatrix<std::vector<int>, std::string>
*/
void TestWays3() {
	{
		AdjacencyMatrix<std::vector<int>, std::string>graph("", "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
		std::vector<int> Node1 = random_element(std::vector<int>());
		size_t pos1 = graph.add_node(Node1);
		std::vector<int> Node2 = random_element(std::vector<int>());
		size_t pos2 = graph.add_node(Node2);
		std::vector<int> Node3 = random_element(std::vector<int>());
		size_t pos3 = graph.add_node(Node3);
		std::vector<int> Node4 = random_element(std::vector<int>());
		size_t pos4 = graph.add_node(Node4);
		std::vector<int> Node5 = random_element(std::vector<int>());
		size_t pos5 = graph.add_node(Node5);
		auto ways = graph.dijkstra_algorithm(pos3);
		for (size_t i = pos1; i < pos5; i++) {
			if (i != pos3) {
				ASSERT_EQUAL(ways[i], "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
			}
		}
		ASSERT_EQUAL(ways[pos3], "");

		graph.add_edge(pos1, pos2, "abcde");
		graph.add_edge(pos1, pos5, "orororand");
		graph.add_edge(pos5, pos3, "dcdc");
		graph.add_edge(pos2, pos5, "ccc");
		graph.add_edge(pos2, pos3, "mlka");

		for (size_t i = pos1; i <= pos5; i++) {
			if (i != pos4) {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos4], "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
			}
			else {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos4], "");
			}
		}

		graph.add_edge(pos4, pos3, "tatl");
		graph.add_edge(pos4, pos2, "krum");

		{
			auto ways = graph.dijkstra_algorithm(pos1);

			ASSERT_EQUAL(ways[pos1], "");
			ASSERT_EQUAL(ways[pos2], "abcde");
			ASSERT_EQUAL(ways[pos3], "abcdecccdcdc");
			ASSERT_EQUAL(ways[pos4], "abcdecccdcdctatl");
			ASSERT_EQUAL(ways[pos5], "abcdeccc");
		}

		{
			auto ways = graph.dijkstra_algorithm(pos2);

			ASSERT_EQUAL(ways[pos1], "abcde");
			ASSERT_EQUAL(ways[pos2], "");
			ASSERT_EQUAL(ways[pos3], "abcdeorororanddcdc");
			ASSERT_EQUAL(ways[pos4], "abcdeorororanddcdctatl");
			ASSERT_EQUAL(ways[pos5], "abcdeorororand");
		}

		{
			auto ways = graph.dijkstra_algorithm(pos3);

			ASSERT_EQUAL(ways[pos1], "dcdccccabcde");
			ASSERT_EQUAL(ways[pos2], "dcdcccc");
			ASSERT_EQUAL(ways[pos3], "");
			ASSERT_EQUAL(ways[pos4], "dcdcccckrum");
			ASSERT_EQUAL(ways[pos5], "dcdc");
		}

		{
			auto ways = graph.dijkstra_algorithm(pos4);

			ASSERT_EQUAL(ways[pos1], "krumabcde");
			ASSERT_EQUAL(ways[pos2], "krum");
			ASSERT_EQUAL(ways[pos3], "krumabcdeorororanddcdc");
			ASSERT_EQUAL(ways[pos4], "");
			ASSERT_EQUAL(ways[pos5], "krumabcdeorororand");
		}

		{
			auto ways = graph.dijkstra_algorithm(pos5);

			ASSERT_EQUAL(ways[pos1], "cccabcde");
			ASSERT_EQUAL(ways[pos2], "ccc");
			ASSERT_EQUAL(ways[pos3], "ccckrumtatl");
			ASSERT_EQUAL(ways[pos4], "ccckrum");
			ASSERT_EQUAL(ways[pos5], "");
		}
	}
	{
		AdjacencyStructure<std::vector<int>, std::string>graph("", "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
		std::vector<int> Node1 = random_element(std::vector<int>());
		size_t pos1 = graph.add_node(Node1);
		std::vector<int> Node2 = random_element(std::vector<int>());
		size_t pos2 = graph.add_node(Node2);
		std::vector<int> Node3 = random_element(std::vector<int>());
		size_t pos3 = graph.add_node(Node3);
		std::vector<int> Node4 = random_element(std::vector<int>());
		size_t pos4 = graph.add_node(Node4);
		std::vector<int> Node5 = random_element(std::vector<int>());
		size_t pos5 = graph.add_node(Node5);
		auto ways = graph.dijkstra_algorithm(pos3);
		for (size_t i = pos1; i < pos5; i++) {
			if (i != pos3) {
				ASSERT_EQUAL(ways[i], "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
			}
		}
		ASSERT_EQUAL(ways[pos3], "");

		graph.add_edge(pos1, pos2, "abcde");
		graph.add_edge(pos1, pos5, "orororand");
		graph.add_edge(pos5, pos3, "dcdc");
		graph.add_edge(pos2, pos5, "ccc");
		graph.add_edge(pos2, pos3, "mlka");

		for (size_t i = pos1; i <= pos5; i++) {
			if (i != pos4) {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos4], "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
			}
			else {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos4], "");
			}
		}

		graph.add_edge(pos4, pos3, "tatl");
		graph.add_edge(pos4, pos2, "krum");

		{
			auto ways = graph.dijkstra_algorithm(pos1);

			ASSERT_EQUAL(ways[pos1], "");
			ASSERT_EQUAL(ways[pos2], "abcde");
			ASSERT_EQUAL(ways[pos3], "abcdecccdcdc");
			ASSERT_EQUAL(ways[pos4], "abcdecccdcdctatl");
			ASSERT_EQUAL(ways[pos5], "abcdeccc");
		}

		{
			auto ways = graph.dijkstra_algorithm(pos2);

			ASSERT_EQUAL(ways[pos1], "abcde");
			ASSERT_EQUAL(ways[pos2], "");
			ASSERT_EQUAL(ways[pos3], "abcdeorororanddcdc");
			ASSERT_EQUAL(ways[pos4], "abcdeorororanddcdctatl");
			ASSERT_EQUAL(ways[pos5], "abcdeorororand");
		}

		{
			auto ways = graph.dijkstra_algorithm(pos3);

			ASSERT_EQUAL(ways[pos1], "dcdccccabcde");
			ASSERT_EQUAL(ways[pos2], "dcdcccc");
			ASSERT_EQUAL(ways[pos3], "");
			ASSERT_EQUAL(ways[pos4], "dcdcccckrum");
			ASSERT_EQUAL(ways[pos5], "dcdc");
		}

		{
			auto ways = graph.dijkstra_algorithm(pos4);

			ASSERT_EQUAL(ways[pos1], "krumabcde");
			ASSERT_EQUAL(ways[pos2], "krum");
			ASSERT_EQUAL(ways[pos3], "krumabcdeorororanddcdc");
			ASSERT_EQUAL(ways[pos4], "");
			ASSERT_EQUAL(ways[pos5], "krumabcdeorororand");
		}

		{
			auto ways = graph.dijkstra_algorithm(pos5);

			ASSERT_EQUAL(ways[pos1], "cccabcde");
			ASSERT_EQUAL(ways[pos2], "ccc");
			ASSERT_EQUAL(ways[pos3], "ccckrumtatl");
			ASSERT_EQUAL(ways[pos4], "ccckrum");
			ASSERT_EQUAL(ways[pos5], "");
		}
	}
}

/**
\brief tests dijkstra_algorithm method for AdjacencyStructure<std::vector<int>, std::string>
*/
void TestWays4() {
	{
		AdjacencyStructure<std::vector<int>, std::string>graph("", "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
		std::vector<int> Node1 = random_element(std::vector<int>());
		size_t pos1 = graph.add_node(Node1);
		std::vector<int> Node2 = random_element(std::vector<int>());
		size_t pos2 = graph.add_node(Node2);
		std::vector<int> Node3 = random_element(std::vector<int>());
		size_t pos3 = graph.add_node(Node3);
		std::vector<int> Node4 = random_element(std::vector<int>());
		size_t pos4 = graph.add_node(Node4);
		std::vector<int> Node5 = random_element(std::vector<int>());
		size_t pos5 = graph.add_node(Node5);
		auto ways = graph.dijkstra_algorithm(pos3);
		for (size_t i = pos1; i < pos5; i++) {
			if (i != pos3) {
				ASSERT_EQUAL(ways[i], "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
			}
		}
		ASSERT_EQUAL(ways[pos3], "");

		graph.add_edge(pos1, pos2, "abcde");
		graph.add_edge(pos1, pos5, "orororand");
		graph.add_edge(pos5, pos3, "dcdc");
		graph.add_edge(pos2, pos5, "ccc");
		graph.add_edge(pos2, pos3, "mlka");

		for (size_t i = pos1; i <= pos5; i++) {
			if (i != pos4) {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos4], "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
			}
			else {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos4], "");
			}
		}

		graph.add_edge(pos4, pos3, "tatl");
		graph.add_edge(pos4, pos2, "krum");

		{
			auto ways = graph.dijkstra_algorithm(pos1);

			ASSERT_EQUAL(ways[pos1], "");
			ASSERT_EQUAL(ways[pos2], "abcde");
			ASSERT_EQUAL(ways[pos3], "abcdecccdcdc");
			ASSERT_EQUAL(ways[pos4], "abcdecccdcdctatl");
			ASSERT_EQUAL(ways[pos5], "abcdeccc");
		}

		{
			auto ways = graph.dijkstra_algorithm(pos2);

			ASSERT_EQUAL(ways[pos1], "abcde");
			ASSERT_EQUAL(ways[pos2], "");
			ASSERT_EQUAL(ways[pos3], "abcdeorororanddcdc");
			ASSERT_EQUAL(ways[pos4], "abcdeorororanddcdctatl");
			ASSERT_EQUAL(ways[pos5], "abcdeorororand");
		}

		{
			auto ways = graph.dijkstra_algorithm(pos3);

			ASSERT_EQUAL(ways[pos1], "dcdccccabcde");
			ASSERT_EQUAL(ways[pos2], "dcdcccc");
			ASSERT_EQUAL(ways[pos3], "");
			ASSERT_EQUAL(ways[pos4], "dcdcccckrum");
			ASSERT_EQUAL(ways[pos5], "dcdc");
		}

		{
			auto ways = graph.dijkstra_algorithm(pos4);

			ASSERT_EQUAL(ways[pos1], "krumabcde");
			ASSERT_EQUAL(ways[pos2], "krum");
			ASSERT_EQUAL(ways[pos3], "krumabcdeorororanddcdc");
			ASSERT_EQUAL(ways[pos4], "");
			ASSERT_EQUAL(ways[pos5], "krumabcdeorororand");
		}

		{
			auto ways = graph.dijkstra_algorithm(pos5);

			ASSERT_EQUAL(ways[pos1], "cccabcde");
			ASSERT_EQUAL(ways[pos2], "ccc");
			ASSERT_EQUAL(ways[pos3], "ccckrumtatl");
			ASSERT_EQUAL(ways[pos4], "ccckrum");
			ASSERT_EQUAL(ways[pos5], "");
		}
	}
	{
		AdjacencyStructure<std::vector<int>, std::string>graph("", "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
		std::vector<int> Node1 = random_element(std::vector<int>());
		size_t pos1 = graph.add_node(Node1);
		std::vector<int> Node2 = random_element(std::vector<int>());
		size_t pos2 = graph.add_node(Node2);
		std::vector<int> Node3 = random_element(std::vector<int>());
		size_t pos3 = graph.add_node(Node3);
		std::vector<int> Node4 = random_element(std::vector<int>());
		size_t pos4 = graph.add_node(Node4);
		std::vector<int> Node5 = random_element(std::vector<int>());
		size_t pos5 = graph.add_node(Node5);
		auto ways = graph.dijkstra_algorithm(pos3);
		for (size_t i = pos1; i < pos5; i++) {
			if (i != pos3) {
				ASSERT_EQUAL(ways[i], "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
			}
		}
		ASSERT_EQUAL(ways[pos3], "");

		graph.add_edge(pos1, pos2, "abcde");
		graph.add_edge(pos1, pos5, "orororand");
		graph.add_edge(pos5, pos3, "dcdc");
		graph.add_edge(pos2, pos5, "ccc");
		graph.add_edge(pos2, pos3, "mlka");

		for (size_t i = pos1; i <= pos5; i++) {
			if (i != pos4) {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos4], "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
			}
			else {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos4], "");
			}
		}

		graph.add_edge(pos4, pos3, "tatl");
		graph.add_edge(pos4, pos2, "krum");

		{
			auto ways = graph.dijkstra_algorithm(pos1);

			ASSERT_EQUAL(ways[pos1], "");
			ASSERT_EQUAL(ways[pos2], "abcde");
			ASSERT_EQUAL(ways[pos3], "abcdecccdcdc");
			ASSERT_EQUAL(ways[pos4], "abcdecccdcdctatl");
			ASSERT_EQUAL(ways[pos5], "abcdeccc");
		}

		{
			auto ways = graph.dijkstra_algorithm(pos2);

			ASSERT_EQUAL(ways[pos1], "abcde");
			ASSERT_EQUAL(ways[pos2], "");
			ASSERT_EQUAL(ways[pos3], "abcdeorororanddcdc");
			ASSERT_EQUAL(ways[pos4], "abcdeorororanddcdctatl");
			ASSERT_EQUAL(ways[pos5], "abcdeorororand");
		}

		{
			auto ways = graph.dijkstra_algorithm(pos3);

			ASSERT_EQUAL(ways[pos1], "dcdccccabcde");
			ASSERT_EQUAL(ways[pos2], "dcdcccc");
			ASSERT_EQUAL(ways[pos3], "");
			ASSERT_EQUAL(ways[pos4], "dcdcccckrum");
			ASSERT_EQUAL(ways[pos5], "dcdc");
		}

		{
			auto ways = graph.dijkstra_algorithm(pos4);

			ASSERT_EQUAL(ways[pos1], "krumabcde");
			ASSERT_EQUAL(ways[pos2], "krum");
			ASSERT_EQUAL(ways[pos3], "krumabcdeorororanddcdc");
			ASSERT_EQUAL(ways[pos4], "");
			ASSERT_EQUAL(ways[pos5], "krumabcdeorororand");
		}

		{
			auto ways = graph.dijkstra_algorithm(pos5);

			ASSERT_EQUAL(ways[pos1], "cccabcde");
			ASSERT_EQUAL(ways[pos2], "ccc");
			ASSERT_EQUAL(ways[pos3], "ccckrumtatl");
			ASSERT_EQUAL(ways[pos4], "ccckrum");
			ASSERT_EQUAL(ways[pos5], "");
		}
	}
}

/**
\brief tests dijkstra_algorithm method for AdjacencyMatrix<BookCharacter<int>, Book>
*/
void TestWays5() {
	{
		AdjacencyMatrix<BookCharacter<int>, Book>graph(Book(), Book("zzzzzzzzzz", {}, Date(), 1000, "zzzzzzzz"));
		BookCharacter<int> Node1 = random_element(BookCharacter<int>());
		size_t pos1 = graph.add_node(Node1);
		BookCharacter<int> Node2 = random_element(BookCharacter<int>());
		size_t pos2 = graph.add_node(Node2);
		BookCharacter<int> Node3 = random_element(BookCharacter<int>());
		size_t pos3 = graph.add_node(Node3);
		BookCharacter<int> Node4 = random_element(BookCharacter<int>());
		size_t pos4 = graph.add_node(Node4);
		auto ways = graph.dijkstra_algorithm(pos3);
		for (size_t i = pos1; i <= pos4; i++) {
			if (i != pos3) {
				ASSERT_EQUAL(ways[i], Book("zzzzzzzzzz", {}, Date(), 1000, "zzzzzzzz"));
			}
		}
		ASSERT_EQUAL(ways[pos3], Book());

		Book edge1("aaa", std::set<std::string>{"baba"}, Date(1, 1, 1, 1, 1, 1), 100, "annot");
		Book edge2("bbb", std::set<std::string>{"abab"}, Date(1, 1, 1, 1, 1, 1), 100, "annot");
		Book edge3("aaa", std::set<std::string>{"abab"}, Date(1, 1, 1, 1, 1, 1), 100, "annot");
		Book edge4("ccc", std::set<std::string>{"abab"}, Date(1, 1, 1, 1, 1, 1), 100, "annot");

		graph.add_edge(pos1, pos3, edge1);
		graph.add_edge(pos3, pos2, edge2);

		for (size_t i = pos1; i <= pos4; i++) {
			if (i != pos4) {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos4], Book("zzzzzzzzzz", {}, Date(), 1000, "zzzzzzzz"));
			}
			else {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos4], Book());
			}
		}

		graph.add_edge(pos1,pos4,edge3);
		graph.add_edge(pos2, pos4, edge4);

		{
			auto ways = graph.dijkstra_algorithm(pos1);

			ASSERT_EQUAL(ways[pos1], Book());
			ASSERT_EQUAL(ways[pos2], edge1+edge2);
			ASSERT_EQUAL(ways[pos3], edge1);
			ASSERT_EQUAL(ways[pos4], edge3);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos2);

			ASSERT_EQUAL(ways[pos1], edge2 + edge1);
			ASSERT_EQUAL(ways[pos2], Book());
			ASSERT_EQUAL(ways[pos3], edge2);
			ASSERT_EQUAL(ways[pos4], edge2+edge1+edge3);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos3);

			ASSERT_EQUAL(ways[pos1], edge1);
			ASSERT_EQUAL(ways[pos2], edge1 + edge3 +edge4);
			ASSERT_EQUAL(ways[pos3], Book());
			ASSERT_EQUAL(ways[pos4], edge1 + edge3);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos4);

			ASSERT_EQUAL(ways[pos1], edge3);
			ASSERT_EQUAL(ways[pos2], edge3 + edge1 +edge2);
			ASSERT_EQUAL(ways[pos3], edge3 + edge1);
			ASSERT_EQUAL(ways[pos4], Book());
		}

	}
	{
		AdjacencyStructure<BookCharacter<int>, Book>graph(Book(), Book("zzzzzzzzzz", {}, Date(), 1000, "zzzzzzzz"));
		BookCharacter<int> Node1 = random_element(BookCharacter<int>());
		size_t pos1 = graph.add_node(Node1);
		BookCharacter<int> Node2 = random_element(BookCharacter<int>());
		size_t pos2 = graph.add_node(Node2);
		BookCharacter<int> Node3 = random_element(BookCharacter<int>());
		size_t pos3 = graph.add_node(Node3);
		BookCharacter<int> Node4 = random_element(BookCharacter<int>());
		size_t pos4 = graph.add_node(Node4);
		auto ways = graph.dijkstra_algorithm(pos3);
		for (size_t i = pos1; i <= pos4; i++) {
			if (i != pos3) {
				ASSERT_EQUAL(ways[i], Book("zzzzzzzzzz", {}, Date(), 1000, "zzzzzzzz"));
			}
		}
		ASSERT_EQUAL(ways[pos3], Book());

		Book edge1("aaa", std::set<std::string>{"baba"}, Date(1, 1, 1, 1, 1, 1), 100, "annot");
		Book edge2("bbb", std::set<std::string>{"abab"}, Date(1, 1, 1, 1, 1, 1), 100, "annot");
		Book edge3("aaa", std::set<std::string>{"abab"}, Date(1, 1, 1, 1, 1, 1), 100, "annot");
		Book edge4("ccc", std::set<std::string>{"abab"}, Date(1, 1, 1, 1, 1, 1), 100, "annot");

		graph.add_edge(pos1, pos3, edge1);
		graph.add_edge(pos3, pos2, edge2);

		for (size_t i = pos1; i <= pos4; i++) {
			if (i != pos4) {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos4], Book("zzzzzzzzzz", {}, Date(), 1000, "zzzzzzzz"));
			}
			else {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos4], Book());
			}
		}

		graph.add_edge(pos1, pos4, edge3);
		graph.add_edge(pos2, pos4, edge4);

		{
			auto ways = graph.dijkstra_algorithm(pos1);

			ASSERT_EQUAL(ways[pos1], Book());
			ASSERT_EQUAL(ways[pos2], edge1 + edge2);
			ASSERT_EQUAL(ways[pos3], edge1);
			ASSERT_EQUAL(ways[pos4], edge3);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos2);

			ASSERT_EQUAL(ways[pos1], edge2 + edge1);
			ASSERT_EQUAL(ways[pos2], Book());
			ASSERT_EQUAL(ways[pos3], edge2);
			ASSERT_EQUAL(ways[pos4], edge2 + edge1 + edge3);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos3);

			ASSERT_EQUAL(ways[pos1], edge1);
			ASSERT_EQUAL(ways[pos2], edge1 + edge3 + edge4);
			ASSERT_EQUAL(ways[pos3], Book());
			ASSERT_EQUAL(ways[pos4], edge1 + edge3);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos4);

			ASSERT_EQUAL(ways[pos1], edge3);
			ASSERT_EQUAL(ways[pos2], edge3 + edge1 + edge2);
			ASSERT_EQUAL(ways[pos3], edge3 + edge1);
			ASSERT_EQUAL(ways[pos4], Book());
		}

	}
}

/**
\brief tests dijkstra_algorithm method for AdjacencyStructure<BookCharacter<int>, Book>
*/
void TestWays6() {
	{
		AdjacencyStructure<BookCharacter<int>, Book>graph(Book(), Book("zzzzzzzzzz", {}, Date(), 1000, "zzzzzzzz"));
		BookCharacter<int> Node1 = random_element(BookCharacter<int>());
		size_t pos1 = graph.add_node(Node1);
		BookCharacter<int> Node2 = random_element(BookCharacter<int>());
		size_t pos2 = graph.add_node(Node2);
		BookCharacter<int> Node3 = random_element(BookCharacter<int>());
		size_t pos3 = graph.add_node(Node3);
		BookCharacter<int> Node4 = random_element(BookCharacter<int>());
		size_t pos4 = graph.add_node(Node4);
		auto ways = graph.dijkstra_algorithm(pos3);
		for (size_t i = pos1; i <= pos4; i++) {
			if (i != pos3) {
				ASSERT_EQUAL(ways[i], Book("zzzzzzzzzz", {}, Date(), 1000, "zzzzzzzz"));
			}
		}
		ASSERT_EQUAL(ways[pos3], Book());

		Book edge1("aaa", std::set<std::string>{"baba"}, Date(1, 1, 1, 1, 1, 1), 100, "annot");
		Book edge2("bbb", std::set<std::string>{"abab"}, Date(1, 1, 1, 1, 1, 1), 100, "annot");
		Book edge3("aaa", std::set<std::string>{"abab"}, Date(1, 1, 1, 1, 1, 1), 100, "annot");
		Book edge4("ccc", std::set<std::string>{"abab"}, Date(1, 1, 1, 1, 1, 1), 100, "annot");

		graph.add_edge(pos1, pos3, edge1);
		graph.add_edge(pos3, pos2, edge2);

		for (size_t i = pos1; i <= pos4; i++) {
			if (i != pos4) {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos4], Book("zzzzzzzzzz", {}, Date(), 1000, "zzzzzzzz"));
			}
			else {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos4], Book());
			}
		}

		graph.add_edge(pos1, pos4, edge3);
		graph.add_edge(pos2, pos4, edge4);

		{
			auto ways = graph.dijkstra_algorithm(pos1);

			ASSERT_EQUAL(ways[pos1], Book());
			ASSERT_EQUAL(ways[pos2], edge1 + edge2);
			ASSERT_EQUAL(ways[pos3], edge1);
			ASSERT_EQUAL(ways[pos4], edge3);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos2);

			ASSERT_EQUAL(ways[pos1], edge2 + edge1);
			ASSERT_EQUAL(ways[pos2], Book());
			ASSERT_EQUAL(ways[pos3], edge2);
			ASSERT_EQUAL(ways[pos4], edge2 + edge1 + edge3);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos3);

			ASSERT_EQUAL(ways[pos1], edge1);
			ASSERT_EQUAL(ways[pos2], edge1 + edge3 + edge4);
			ASSERT_EQUAL(ways[pos3], Book());
			ASSERT_EQUAL(ways[pos4], edge1 + edge3);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos4);

			ASSERT_EQUAL(ways[pos1], edge3);
			ASSERT_EQUAL(ways[pos2], edge3 + edge1 + edge2);
			ASSERT_EQUAL(ways[pos3], edge3 + edge1);
			ASSERT_EQUAL(ways[pos4], Book());
		}

	}
	{
		AdjacencyStructure<BookCharacter<int>, Book>graph(Book(), Book("zzzzzzzzzz", {}, Date(), 1000, "zzzzzzzz"));
		BookCharacter<int> Node1 = random_element(BookCharacter<int>());
		size_t pos1 = graph.add_node(Node1);
		BookCharacter<int> Node2 = random_element(BookCharacter<int>());
		size_t pos2 = graph.add_node(Node2);
		BookCharacter<int> Node3 = random_element(BookCharacter<int>());
		size_t pos3 = graph.add_node(Node3);
		BookCharacter<int> Node4 = random_element(BookCharacter<int>());
		size_t pos4 = graph.add_node(Node4);
		auto ways = graph.dijkstra_algorithm(pos3);
		for (size_t i = pos1; i <= pos4; i++) {
			if (i != pos3) {
				ASSERT_EQUAL(ways[i], Book("zzzzzzzzzz", {}, Date(), 1000, "zzzzzzzz"));
			}
		}
		ASSERT_EQUAL(ways[pos3], Book());

		Book edge1("aaa", std::set<std::string>{"baba"}, Date(1, 1, 1, 1, 1, 1), 100, "annot");
		Book edge2("bbb", std::set<std::string>{"abab"}, Date(1, 1, 1, 1, 1, 1), 100, "annot");
		Book edge3("aaa", std::set<std::string>{"abab"}, Date(1, 1, 1, 1, 1, 1), 100, "annot");
		Book edge4("ccc", std::set<std::string>{"abab"}, Date(1, 1, 1, 1, 1, 1), 100, "annot");

		graph.add_edge(pos1, pos3, edge1);
		graph.add_edge(pos3, pos2, edge2);

		for (size_t i = pos1; i <= pos4; i++) {
			if (i != pos4) {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos4], Book("zzzzzzzzzz", {}, Date(), 1000, "zzzzzzzz"));
			}
			else {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos4], Book());
			}
		}

		graph.add_edge(pos1, pos4, edge3);
		graph.add_edge(pos2, pos4, edge4);

		{
			auto ways = graph.dijkstra_algorithm(pos1);

			ASSERT_EQUAL(ways[pos1], Book());
			ASSERT_EQUAL(ways[pos2], edge1 + edge2);
			ASSERT_EQUAL(ways[pos3], edge1);
			ASSERT_EQUAL(ways[pos4], edge3);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos2);

			ASSERT_EQUAL(ways[pos1], edge2 + edge1);
			ASSERT_EQUAL(ways[pos2], Book());
			ASSERT_EQUAL(ways[pos3], edge2);
			ASSERT_EQUAL(ways[pos4], edge2 + edge1 + edge3);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos3);

			ASSERT_EQUAL(ways[pos1], edge1);
			ASSERT_EQUAL(ways[pos2], edge1 + edge3 + edge4);
			ASSERT_EQUAL(ways[pos3], Book());
			ASSERT_EQUAL(ways[pos4], edge1 + edge3);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos4);

			ASSERT_EQUAL(ways[pos1], edge3);
			ASSERT_EQUAL(ways[pos2], edge3 + edge1 + edge2);
			ASSERT_EQUAL(ways[pos3], edge3 + edge1);
			ASSERT_EQUAL(ways[pos4], Book());
		}

	}
}

/**
\brief tests dijkstra_algorithm method for AdjacencyMatrix<PublishingHouse, Date>
*/
void TestWays7() {
	{
		AdjacencyMatrix<PublishingHouse, Date>graph(Date(), Date(1000, 1000, 1000, 1000, 1000, 10000)); 
		PublishingHouse Node1 = random_element(PublishingHouse());
		size_t pos1 = graph.add_node(Node1);
		PublishingHouse Node2 = random_element(PublishingHouse());
		size_t pos2 = graph.add_node(Node2);
		PublishingHouse Node3 = random_element(PublishingHouse());
		size_t pos3 = graph.add_node(Node3);
		PublishingHouse Node4 = random_element(PublishingHouse());
		size_t pos4 = graph.add_node(Node4);
		auto ways = graph.dijkstra_algorithm(pos3);
		for (size_t i = pos1; i <= pos4; i++) {
			if (i != pos3) {
				ASSERT_EQUAL(ways[i], Date(1000, 1000, 1000, 1000, 1000, 10000));
			}
		}
		ASSERT_EQUAL(ways[pos3], Date());

		Date edge1(0,0,0,4,10,2020);
		Date edge2(0,0,0,5,10,2020);
		Date edge3(0,0,12,3,10,2020);
		Date edge4(0,0,12,1,1,2021);

		graph.add_edge(pos1, pos3, edge1);
		graph.add_edge(pos1, pos4, edge4);

		for (size_t i = pos1; i <= pos4; i++) {
			if (i != pos2) {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos2], Date(1000, 1000, 1000, 1000, 1000, 10000));
			}
			else {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos2], Date());
			}
		}

		graph.add_edge(pos2, pos4, edge3);
		graph.add_edge(pos2, pos3, edge2);

		{
			auto ways = graph.dijkstra_algorithm(pos1);

			ASSERT_EQUAL(ways[pos1], Date());
			ASSERT_EQUAL(ways[pos2], edge1 + edge2);
			ASSERT_EQUAL(ways[pos3], edge1);
			ASSERT_EQUAL(ways[pos4], edge1 + edge2+edge3);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos2);

			ASSERT_EQUAL(ways[pos1], edge3 + edge4);
			ASSERT_EQUAL(ways[pos2], Date());
			ASSERT_EQUAL(ways[pos3], edge3+edge4+edge1);
			ASSERT_EQUAL(ways[pos4], edge3);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos3);

			ASSERT_EQUAL(ways[pos1], edge1);
			ASSERT_EQUAL(ways[pos2], edge2);
			ASSERT_EQUAL(ways[pos3], Date());
			ASSERT_EQUAL(ways[pos4], edge1 + edge4);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos4);

			ASSERT_EQUAL(ways[pos1], edge3+edge2+edge1);
			ASSERT_EQUAL(ways[pos2], edge3);
			ASSERT_EQUAL(ways[pos3], edge3+edge2);
			ASSERT_EQUAL(ways[pos4], Date());
		}
	}
	{
		AdjacencyStructure<PublishingHouse, Date>graph(Date(), Date(1000, 1000, 1000, 1000, 1000, 10000));
		PublishingHouse Node1 = random_element(PublishingHouse());
		size_t pos1 = graph.add_node(Node1);
		PublishingHouse Node2 = random_element(PublishingHouse());
		size_t pos2 = graph.add_node(Node2);
		PublishingHouse Node3 = random_element(PublishingHouse());
		size_t pos3 = graph.add_node(Node3);
		PublishingHouse Node4 = random_element(PublishingHouse());
		size_t pos4 = graph.add_node(Node4);
		auto ways = graph.dijkstra_algorithm(pos3);
		for (size_t i = pos1; i <= pos4; i++) {
			if (i != pos3) {
				ASSERT_EQUAL(ways[i], Date(1000, 1000, 1000, 1000, 1000, 10000));
			}
		}
		ASSERT_EQUAL(ways[pos3], Date());

		Date edge1(0, 0, 0, 4, 10, 2020);
		Date edge2(0, 0, 0, 5, 10, 2020);
		Date edge3(0, 0, 12, 3, 10, 2020);
		Date edge4(0, 0, 12, 1, 1, 2021);

		graph.add_edge(pos1, pos3, edge1);
		graph.add_edge(pos1, pos4, edge4);

		for (size_t i = pos1; i <= pos4; i++) {
			if (i != pos2) {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos2], Date(1000, 1000, 1000, 1000, 1000, 10000));
			}
			else {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos2], Date());
			}
		}

		graph.add_edge(pos2, pos4, edge3);
		graph.add_edge(pos2, pos3, edge2);

		{
			auto ways = graph.dijkstra_algorithm(pos1);

			ASSERT_EQUAL(ways[pos1], Date());
			ASSERT_EQUAL(ways[pos2], edge1 + edge2);
			ASSERT_EQUAL(ways[pos3], edge1);
			ASSERT_EQUAL(ways[pos4], edge1 + edge2 + edge3);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos2);

			ASSERT_EQUAL(ways[pos1], edge3 + edge4);
			ASSERT_EQUAL(ways[pos2], Date());
			ASSERT_EQUAL(ways[pos3], edge3 + edge4 + edge1);
			ASSERT_EQUAL(ways[pos4], edge3);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos3);

			ASSERT_EQUAL(ways[pos1], edge1);
			ASSERT_EQUAL(ways[pos2], edge2);
			ASSERT_EQUAL(ways[pos3], Date());
			ASSERT_EQUAL(ways[pos4], edge1 + edge4);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos4);

			ASSERT_EQUAL(ways[pos1], edge3 + edge2 + edge1);
			ASSERT_EQUAL(ways[pos2], edge3);
			ASSERT_EQUAL(ways[pos3], edge3 + edge2);
			ASSERT_EQUAL(ways[pos4], Date());
		}
	}
}

/**
\brief tests dijkstra_algorithm method for AdjacencyStructure<PublishingHouse, Date>
*/
void TestWays8() {
	{
		AdjacencyStructure<PublishingHouse, Date>graph(Date(), Date(1000, 1000, 1000, 1000, 1000, 10000));
		PublishingHouse Node1 = random_element(PublishingHouse());
		size_t pos1 = graph.add_node(Node1);
		PublishingHouse Node2 = random_element(PublishingHouse());
		size_t pos2 = graph.add_node(Node2);
		PublishingHouse Node3 = random_element(PublishingHouse());
		size_t pos3 = graph.add_node(Node3);
		PublishingHouse Node4 = random_element(PublishingHouse());
		size_t pos4 = graph.add_node(Node4);
		auto ways = graph.dijkstra_algorithm(pos3);
		for (size_t i = pos1; i <= pos4; i++) {
			if (i != pos3) {
				ASSERT_EQUAL(ways[i], Date(1000, 1000, 1000, 1000, 1000, 10000));
			}
		}
		ASSERT_EQUAL(ways[pos3], Date());

		Date edge1(0, 0, 0, 4, 10, 2020);
		Date edge2(0, 0, 0, 5, 10, 2020);
		Date edge3(0, 0, 12, 3, 10, 2020);
		Date edge4(0, 0, 12, 1, 1, 2021);

		graph.add_edge(pos1, pos3, edge1);
		graph.add_edge(pos1, pos4, edge4);

		for (size_t i = pos1; i <= pos4; i++) {
			if (i != pos2) {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos2], Date(1000, 1000, 1000, 1000, 1000, 10000));
			}
			else {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos2], Date());
			}
		}

		graph.add_edge(pos2, pos4, edge3);
		graph.add_edge(pos2, pos3, edge2);

		{
			auto ways = graph.dijkstra_algorithm(pos1);

			ASSERT_EQUAL(ways[pos1], Date());
			ASSERT_EQUAL(ways[pos2], edge1 + edge2);
			ASSERT_EQUAL(ways[pos3], edge1);
			ASSERT_EQUAL(ways[pos4], edge1 + edge2 + edge3);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos2);

			ASSERT_EQUAL(ways[pos1], edge3 + edge4);
			ASSERT_EQUAL(ways[pos2], Date());
			ASSERT_EQUAL(ways[pos3], edge3 + edge4 + edge1);
			ASSERT_EQUAL(ways[pos4], edge3);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos3);

			ASSERT_EQUAL(ways[pos1], edge1);
			ASSERT_EQUAL(ways[pos2], edge2);
			ASSERT_EQUAL(ways[pos3], Date());
			ASSERT_EQUAL(ways[pos4], edge1 + edge4);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos4);

			ASSERT_EQUAL(ways[pos1], edge3 + edge2 + edge1);
			ASSERT_EQUAL(ways[pos2], edge3);
			ASSERT_EQUAL(ways[pos3], edge3 + edge2);
			ASSERT_EQUAL(ways[pos4], Date());
		}
	}
	{
		AdjacencyStructure<PublishingHouse, Date>graph(Date(), Date(1000, 1000, 1000, 1000, 1000, 10000));
		PublishingHouse Node1 = random_element(PublishingHouse());
		size_t pos1 = graph.add_node(Node1);
		PublishingHouse Node2 = random_element(PublishingHouse());
		size_t pos2 = graph.add_node(Node2);
		PublishingHouse Node3 = random_element(PublishingHouse());
		size_t pos3 = graph.add_node(Node3);
		PublishingHouse Node4 = random_element(PublishingHouse());
		size_t pos4 = graph.add_node(Node4);
		auto ways = graph.dijkstra_algorithm(pos3);
		for (size_t i = pos1; i <= pos4; i++) {
			if (i != pos3) {
				ASSERT_EQUAL(ways[i], Date(1000, 1000, 1000, 1000, 1000, 10000));
			}
		}
		ASSERT_EQUAL(ways[pos3], Date());

		Date edge1(0, 0, 0, 4, 10, 2020);
		Date edge2(0, 0, 0, 5, 10, 2020);
		Date edge3(0, 0, 12, 3, 10, 2020);
		Date edge4(0, 0, 12, 1, 1, 2021);

		graph.add_edge(pos1, pos3, edge1);
		graph.add_edge(pos1, pos4, edge4);

		for (size_t i = pos1; i <= pos4; i++) {
			if (i != pos2) {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos2], Date(1000, 1000, 1000, 1000, 1000, 10000));
			}
			else {
				ASSERT_EQUAL(graph.dijkstra_algorithm(i)[pos2], Date());
			}
		}

		graph.add_edge(pos2, pos4, edge3);
		graph.add_edge(pos2, pos3, edge2);

		{
			auto ways = graph.dijkstra_algorithm(pos1);

			ASSERT_EQUAL(ways[pos1], Date());
			ASSERT_EQUAL(ways[pos2], edge1 + edge2);
			ASSERT_EQUAL(ways[pos3], edge1);
			ASSERT_EQUAL(ways[pos4], edge1 + edge2 + edge3);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos2);

			ASSERT_EQUAL(ways[pos1], edge3 + edge4);
			ASSERT_EQUAL(ways[pos2], Date());
			ASSERT_EQUAL(ways[pos3], edge3 + edge4 + edge1);
			ASSERT_EQUAL(ways[pos4], edge3);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos3);

			ASSERT_EQUAL(ways[pos1], edge1);
			ASSERT_EQUAL(ways[pos2], edge2);
			ASSERT_EQUAL(ways[pos3], Date());
			ASSERT_EQUAL(ways[pos4], edge1 + edge4);
		}

		{
			auto ways = graph.dijkstra_algorithm(pos4);

			ASSERT_EQUAL(ways[pos1], edge3 + edge2 + edge1);
			ASSERT_EQUAL(ways[pos2], edge3);
			ASSERT_EQUAL(ways[pos3], edge3 + edge2);
			ASSERT_EQUAL(ways[pos4], Date());
		}
	}
}

/**
\brief launches tests for graphs
*/
void TestGraph() {
	{
		AdjacencyMatrix<double, int>graph(0, 1000);
		TestBasic(graph);
		TestConnectedComponentsAcyclicTree(graph);
	}
	{
		AdjacencyStructure<double, int>graph(0, 1000);
		TestBasic(graph);
		TestConnectedComponentsAcyclicTree(graph);
	}
	{
		AdjacencyMatrix<int,double>graph(0, 1000);
		TestBasic(graph);
		TestConnectedComponentsAcyclicTree(graph);
	}
	{
		AdjacencyStructure<int, double>graph(0, 1000);
		TestBasic(graph);
		TestConnectedComponentsAcyclicTree(graph);
	}
	{
		AdjacencyMatrix<std::string, std::vector<int>>graph(std::vector<int>(), std::vector<int>(1000,1000));
		TestBasic(graph);
		TestConnectedComponentsAcyclicTree(graph);
	}
	{
		AdjacencyStructure<std::string, std::vector<int>>graph(std::vector<int>(), std::vector<int>(1000, 1000));
		TestBasic(graph);
		TestConnectedComponentsAcyclicTree(graph);
	}
	{
		AdjacencyMatrix<std::vector<int>,std::string>graph("", "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
		TestBasic(graph);
		TestConnectedComponentsAcyclicTree(graph);
	}
	{
		AdjacencyStructure<std::vector<int>,std::string>graph("", "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
		TestBasic(graph);
		TestConnectedComponentsAcyclicTree(graph);
	}
	{
		AdjacencyMatrix<double,std::vector<std::string>>graph(std::vector<std::string>(), std::vector<std::string>(1000, "z"));
		TestBasic(graph);
		TestConnectedComponentsAcyclicTree(graph);
	}
	{
		AdjacencyStructure<double,std::vector<std::string>>graph(std::vector<std::string>(), std::vector<std::string>(1000, "z"));
		TestBasic(graph);
		TestConnectedComponentsAcyclicTree(graph);
	}
	{
		AdjacencyMatrix<BookCharacter<int>, Book>graph(Book(), Book("zzzzzzzzzz", {},Date(),1000,"zzzzzzzz"));
		TestBasic(graph);
		TestConnectedComponentsAcyclicTree(graph);
	}
	{
		AdjacencyStructure<BookCharacter<int>, Book>graph(Book(), Book("zzzzzzzzzz", {}, Date(), 1000, "zzzzzzzz"));
		TestBasic(graph);
		TestConnectedComponentsAcyclicTree(graph);
	}
	{
		AdjacencyMatrix<PublishingHouse, Date>graph(Date(0,0,0,0,0,0), Date(1000, 1000, 1000, 1000, 1000, 1000));
		TestBasic(graph);
		TestConnectedComponentsAcyclicTree(graph);
	}
	{
		AdjacencyStructure<PublishingHouse, Date>graph(Date(0, 0, 0, 0, 0, 0), Date(1000, 1000, 1000, 1000, 1000, 1000));
		TestBasic(graph);
		TestConnectedComponentsAcyclicTree(graph);
	}
	TestWays1();
	TestWays2();
	TestWays3();
	TestWays4();
	TestWays5();
	TestWays6();
	TestWays7();
	TestWays8();
}

//Resources
//https://stackoverflow.com/questions/28261805/c-private-class-member-variables-dont-appear-in-the-documentation
//https://stackoverflow.com/questions/1102392/how-can-i-use-stdmaps-with-user-defined-types-as-key
//https://habr.com/ru/post/252101/

//https://www.coursera.org/learn/c-plus-plus-red
//https://www.coursera.org/learn/c-plus-plus-red/supplement/xZMU3/obnovlionnyi-test-runner-h
//https://www.coursera.org/learn/c-plus-plus-red/supplement/m49r2/profile-h

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestBookCharacter);
	RUN_TEST(tr, TestBook);
	RUN_TEST(tr, TestHouse);
	RUN_TEST(tr, TestDate);
	RUN_TEST(tr, TestGraph);
}
