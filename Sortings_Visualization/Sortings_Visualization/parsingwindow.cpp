#include "parsingwindow.h"
#include "ui_parsingwindow.h"
#include "parser.h"
#include <iostream>


using namespace std;
int parser(const string& input);

//queue<char> to_revpol(const QString &input);
//double calc(queue<char> in);
//void test(const string& input, int pos, int &complexity_quadr,int& complexity_log,int& temp_comp_quad );
ParsingWindow::ParsingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParsingWindow)
{
    ui->setupUi(this);
}

ParsingWindow::~ParsingWindow()
{
    delete ui;
}
/// <summary>
/// Method for clicking a button which calculates computational complexity
/// </summary>
void ParsingWindow::on_pushButton_clicked()
{

 Component *simple = new Leaf;
   std::cout << "Client: I've got a simple component:\n";
   //Simple_tree(simple);
 //QString qstr = QString::fromStdString(Simple_tree(simple));

      //ui->theorComplexity->setText(qstr);
      std::cout << "\n\n";
      Component *tree = new Composite;
        Component *branch1 = new Composite;
        Component *branch2 = new Composite;
        Component *leaf_1 = new Leaf;
          Component *leaf_2 = new Leaf;
          Component *leaf_3 = new Leaf;
          Component *branch4 = new Composite;
          branch1->Add(leaf_1);
            branch1->Add(leaf_2);
            branch2->Add(branch1);
           branch4->Add(branch2);
            Component *branch3 = new Composite;
            branch3->Add(leaf_3);
            tree->Add(branch1);
            tree->Add(branch2);
            tree->Add(branch3);
            tree->Add(branch4);
            std::cout << "Client: Now I've got a composite tree:\n";
            //Simple_tree(tree);
            QString qstr = QString::fromStdString(Simple_tree(tree));
            string input = Simple_tree(tree);
            ui->theorComplexity->setText(qstr);
            std::cout << "\n\n";
            std::cout << "Client: I don't need to check the components classes even when managing the tree:\n";
              //Complex_tree(tree, simple);
             // QString qstr1 = QString::fromStdString(Complex_tree(tree,simple));
              std::cout << "\n";
              //int res = branch1->GetValue() + branch2->GetValue() + branch3->GetValue();
              int res = parser(input);
              ui->res->setText("O(n^" +QString::number(res) + ") ");

            delete simple;
              delete tree;
              delete branch1;
              delete branch2;
              delete leaf_1;
              delete leaf_2;
              delete leaf_3;
//    QString input = ui->inputLine->text();
//    string in = input.toLocal8Bit().constData();
//    int pos = 0;
//    int complexity_quadr = 0;
//    int complexity_log = 0;
//    int temp_comp_quad = 0;
//    test(in,pos,complexity_quadr, complexity_log, temp_comp_quad);
// ui->theorComplexity->setText("О(n^"  + QString::number(complexity_quadr) + ") " + QString::number(complexity_log) );
}
/// <summary>
/// Method which parse the string.
/// </summary>
/// <returns>
/// A value of computational complexity.
/// </returns>
int parser(const string& input)
{
    int flag = 0;
     std::vector<int> max_val;
    for(int i = 0; i < input.length(); i++) {
        if (input[i] == '(') {
            flag++;
            max_val.push_back(flag);
        } else if (input[i] == ')') {
            flag--;
        }
    }
    int max = *max_element(max_val.begin(), max_val.end());
    return max;
}
//bool check_substr(string text,string substring){
//    int found = text.find(substring);
//    if (found != std::string::npos)
//    {
//        return true;
//    }
//    return false;
//}
//void test(const string& in, int pos, int &complexity_quadr, int& complexity_log,int& temp_complex_quad ) {

//    // string in = input.toLocal8Bit().constData();


//     if (pos == in.length()) {return;}



//     if(check_substr(in.substr(pos,in.length()),"loop")){
//        complexity_quadr++;
//    cout<<complexity_quadr << endl;
//     }
//     if (check_substr(in.substr(pos,in.length()),");")) {
//         temp_complex_quad = complexity_quadr;
//         complexity_quadr = 0;
//         if(check_substr(in.substr(pos,in.length()),"loop")){
//            complexity_quadr++;

//            //cout<<temp_complex_quad << endl;
//         }
//     }
//     if (check_substr(in.substr(pos,in.length()),"loop{n/2}")){

//        complexity_log = log(3);
//     }

//     for(int i= pos; i < in.length(); i++){
//        if(in[i] == '(' ) {
//            pos = i;
//            test(in, pos+1,complexity_quadr, complexity_log,temp_complex_quad);
//        }
//     }
//    if (temp_complex_quad > complexity_quadr) {
//        complexity_quadr = temp_complex_quad;
//     //cout<<complexity << endl;
//    }

//}



