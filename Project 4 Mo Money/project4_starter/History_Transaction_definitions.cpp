#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//



// Constructor
// TASK 1
//



// Destructor
// TASK 1
//


// Overloaded < operator.
// TASK 2
//

Transaction::Transaction(std::string ticker_symbol, unsigned int day_date, unsigned int month_date, unsigned year_date, bool buy_sell_trans, unsigned int number_shares, double trans_amount)
{
    day = day_date;
    month = month_date;
    year = year_date;
    trans_type = (buy_sell_trans) ? "Buy" : "Sell";
    symbol = ticker_symbol;
    amount = trans_amount;
    shares = number_shares;
    trans_id = assigned_trans_id;
    /*
    month_date = get_month();
    year_date = get_year();
    buy_sell_trans = get_trans_type();
    ticker_symbol = get_symbol();
    trans_amount = get_amount();
    number_shares = get_shares();*/
    
    //std::cout << trans_id << std::endl;
    //if(trans_id < 0.6)trans_id = assigned_trans_id;
    set_acb(0);
    set_acb_per_share(0);
    set_cgl(0);
    set_share_balance(0);
    //std::cout << day << " " << month << " " << year << " " << trans_type << " " <<  shares << " " << amount << std::endl;
    //trans_id++
    assigned_trans_id++;

    std::cout << trans_id << std::endl;
}

Transaction::~Transaction()
{

}

bool Transaction::operator<(Transaction const& other)
{
    //something is not working here
    if (get_year() < other.get_year()) {
        return true;
    } else if (get_month() == other.get_month()) {
        if (get_month() < other.get_month()) {
            return true;
        } else if (get_month() == other.get_month()) {
            if (get_day() < other.get_day()) {
                return true;
            } else if (get_day() == other.get_day()) {
                if (get_trans_id() > other.get_trans_id()) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}

// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }

double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }

bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
    << std::setw(4) << get_symbol() << " "
    << std::setw(4) << get_day() << " "
    << std::setw(4) << get_month() << " "
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() ) {
    std::cout << "  Buy  ";
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " "
    << std::setw(10) << get_amount() << " "
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl()
    << std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//


// Constructor
// TASK 3
//

History::History() {
    p_head = nullptr;
}



// Destructor
// TASK 3
//

History::~History() {
    Transaction* p_dealloc1 = p_head;
    while (p_dealloc1 != nullptr) {
        Transaction* p_dealloc2 = p_dealloc1->get_next();
        delete p_dealloc1;
        p_dealloc1 = p_dealloc2;
    }
}

void History::read_history()
{/*
    Transaction test1{ "@", 04, 05, 06, true, 456, 34.67 }; //may 4th
    Transaction test2{ "@", 05, 05, 06, false, 436, 78.33 }; //may 5th
    std::cout << (test1 < test2) << std::endl;
    std::cout << (test2 < test1) << std::endl;*/
    ece150::open_file();    
    do {
        insert(new Transaction{ ece150::get_trans_symbol(), ece150::get_trans_day(), ece150::get_trans_month(), ece150::get_trans_year(), ece150::get_trans_type(), ece150::get_trans_shares(), ece150::get_trans_amount() });
    } while (ece150::next_trans_entry());
    ece150::close_file();
}

void History::insert(Transaction* p_new_trans)
{
    /*
    if (p_head == nullptr) {
        p_new_trans->set_next(nullptr);
    } else {
        p_new_trans->set_next(p_head);
        p_head->set_next(nullptr);
    }v

    for ( p_temp->get_next() != nullptr; ) {
        if (p_temp->get_next() == nullptr) {

        }
    }*/
    
    if (p_head != nullptr) {
        bool end;
        Transaction* p_temp = p_head;
        do {
            if (p_temp->get_next() != nullptr) {
                Transaction* p_transfer = p_temp->get_next();
                p_temp = p_transfer;
                std::cout << "transfer" << std::endl;
            } else {
                p_temp->set_next(p_new_trans);
                std::cout << "existing" << std::endl;
                break;
            }

            

        } while (p_temp->get_next() != nullptr);
    } else {
        p_new_trans->set_next(nullptr);
        p_head = p_new_trans;
        std::cout << "new" << std::endl;
    }
    
}


/*p_new_trans->set_next(nullptr);
    
    for (Transaction* p_temp = p_head; p_temp->get_next() != nullptr; p_temp->set_next(p_temp->get_next())) {
        if (p_temp->get_next() == nullptr) {

        }
    }

    do{

    }

    Transaction* p_temp = p_head;
    Transaction* p_temp2 = p_temp->get_next();
    while (p_temp2->get_next() != nullptr) {

    }*/

void History::sort_by_date()
{

}

void History::update_acb_cgl()
{
}

double History::compute_cgl(unsigned int year)
{
    return 0.0;
}


// read_history(...): Read the transaction history from file.
// TASK 4
//

// insert(...): Insert transaction into linked list.
// TASK 5
//


// sort_by_date(): Sort the linked list by trade date.
// TASK 6
//


// update_acb_cgl(): Updates the ACB and CGL values.
// TASK 7
//



// compute_cgl(): )Compute the ACB, and CGL.
// TASK 8




// print() Print the transaction history.
//TASK 9
//



void History::print()
{
}

// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }
