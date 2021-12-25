#pragma once

#include <cstdint>

template <typename DefectTypeId>
class Defect
{
public:
	Defect(DefectTypeId defect_type,uint64_t start);

    DefectTypeId get_defect_type();
	bool is_fixed() const;
	void fix(uint64_t finish);
	uint64_t get_duration() const;
    void set_detected();
    bool is_detected() const;
private:
    DefectTypeId defect_type;
	bool fixed;
    bool detected;
	uint64_t start;
	uint64_t finish;
};

template <typename DefectTypeId>
Defect<DefectTypeId>::Defect(DefectTypeId defect_type, uint64_t start) {
    this->defect_type = defect_type;
    this->fixed = false;
    this->detected = true;
    this->start = start;
    this->finish = 0;
}

template <typename DefectTypeId>
DefectTypeId Defect<DefectTypeId>::get_defect_type()
{
    return this->defect_type;
}

template <typename DefectTypeId>
bool Defect<DefectTypeId>::is_fixed() const
{
    return this->fixed;
}

template <typename DefectTypeId>
void Defect<DefectTypeId>::fix(uint64_t finish)
{
    this->fixed = true;
    this->finish = finish;
}

template <typename DefectTypeId>
uint64_t Defect<DefectTypeId>::get_duration() const
{
    if (fixed) {
        return finish - start;
    }
    else {
        return 0;
    }
}

template<typename DefectTypeId>
void Defect<DefectTypeId>::set_detected()
{
    detected = true;
}

template<typename DefectTypeId>
bool Defect<DefectTypeId>::is_detected() const
{
    return detected;
}