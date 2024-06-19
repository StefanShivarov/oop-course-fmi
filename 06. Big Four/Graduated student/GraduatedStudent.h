#pragma once
class GraduatedStudent
{
public:
    GraduatedStudent(const char* name, const int* grades, size_t gradesCount, const char* quote);

    GraduatedStudent(const GraduatedStudent& other);
    GraduatedStudent& operator=(const GraduatedStudent& other);

    ~GraduatedStudent();

    const char* getName() const;
    const int* getGrades() const;
    size_t getGradesCount() const;
    const char* getQuote() const;

    void setName(const char* str);
    void setGrades(const int* grades, size_t count);
    void setQuote(const char* str);
private:
    char* name = nullptr;
    int* grades = nullptr;
    size_t gradesCount = 0;
    char quote[31] = "";

    void free();
    void copyFrom(const GraduatedStudent& other);
};
