#include "StudentTicket.h"

StudentTicket::StudentTicket(const MyString& name, double price) : Ticket(name, price / 2) {}
