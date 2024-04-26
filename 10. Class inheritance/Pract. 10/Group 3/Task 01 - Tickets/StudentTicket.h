#pragma once
#include "Ticket.h"

class StudentTicket : public Ticket
{
public:
    StudentTicket() = default;
    StudentTicket(const MyString& name, double price);
};

