/*******************************************************************************
\File test.hpp
\Author Timothy Lee Ke xin
\Par DP email: timothykexin.lee@digipen.edu.sg
\Par Course: RSE 1202
\Par Section: Vector Template Abstract Data Type
\Par Programming Lab #9
\Date 15-03-2022

  \Brief
   The purpose of this laboratory is to learn and practice error handling. 
   Error handling of ints and inputs from the istream. For this program, the 
   only valid inputs are integers. If a string or anything other than an int, 
   e.g. Abc, a literal comma, or even if there isn't an input. The program would
   register and identify the errors associated and print it out. Another error 
   can occur from running the functions where an int is divided by 0, it prints 
   the error and the program stops. Upon successful execution, it'll print out 
   the result. Functions test 1 to 5 checks the division of a numerator and a 
   different denominator and the result or error is printed.


- stream_wrapper
    Non-default constructor using the std::istream is param to initialize
    the private object for operator>> function use.

- operator>>
    Class template operator >>. Checks the istream input for valid int 
    inputs and accepts it, and returns a pointer to this. Else it throws an
    error and catches the error and calls the what() function before 
    exiting.

- what
    Virtual const char pointer as the return. When this function is called, 
    it returns a message to explain to the user of the type of error that 
    was caught, rather than vague abort or so message.
    
- division_by_zero
    Non-default constructor for when a division by 0 occurs and this 
    function is thrown with the param containing the value.
    
- what
    Virtual const char pointer as the return. For the division by zero 
    error. When this function is called, it returns a message to explain to
    the user of the type of error that was caught, rather than vague abort 
    or so message.
    
- test1
    Tests if the first denominator can be divided by the numerator. Prints the
    results if successful, otherwise, throws a division_by_zero error 
    containing the numerator and prints the error type message.
    
- test2
    Tests if the second denominator can be divided by the numerator. Prints the
    results if successful, otherwise, throws a division_by_zero error 
    containing the numerator and prints the error type message.
    
- test3
    Tests if the third denominator can be divided by the numerator. Prints the
    results if successful, otherwise, throws a division_by_zero error 
    containing the numerator and prints the error type message.
    
- test4
    Tests if the fourth denominator can be divided by the numerator. Prints the
    results if successful, otherwise, throws a division_by_zero error 
    containing the numerator and prints the error type message.
    
- test5
    Tests if the fifth denominator can be divided by the numerator. Prints the
    results if successful, otherwise, throws a division_by_zero error 
    containing the numerator and prints the error type message.
    
*******************************************************************************/
#include <iostream> 
#include <initializer_list>

namespace hlp2{
class stream_wrapper : public std::exception {
private:
    std::istream &io;

public:

    /**************************************************************************/
    /*!
        \brief
        Non-default constructor using the std::istream is param to initialize
        the private object for operator>> function use.

        \param is
        Creates a reference of the istream object.
    */
    /**************************************************************************/
    stream_wrapper(std::istream& is) : io{is} {}
    

    /**************************************************************************/
    /*!
        \brief
        Class template operator >>. Checks the istream input for valid int 
        inputs and accepts it, and returns a pointer to this. Else it throws an
        error and catches the error and calls the what() function before 
        exiting.

        \param is
        Creates a reference of the istream object.

    */
    /**************************************************************************/
    template <typename T>
    stream_wrapper& operator>> (T& is) {
        try {
            //std::ws discards leading whitespace from istream
            io >> std::ws;
            //peek() returns next character input sequence, without extracting
            if (!isdigit(io.peek())) 
                throw stream_wrapper{io}; 
            io >> is;
            return *this;
        } 
        catch(stream_wrapper const& se){
            std::cout << se.what() << '\n';
            exit(EXIT_SUCCESS);
        }
    }


    /**************************************************************************/
    /*!
        \brief
        Virtual const char pointer as the return. When this function is called, 
        it returns a message to explain to the user of the type of error that 
        was caught, rather than vague abort or so message.

        \param msg
        The string message to be sent when an error is caught and the function
        is called to explain to the user, the type of fault.

    */
    /**************************************************************************/
    virtual const char* what() const noexcept{
        static std::string msg;
        msg = "\nException was thrown: ";
        msg += "Invalid input!";
        //c_str() Returns a pointer to an array that contains a null-terminated 
        //sequence of characters (i.e., a C-string) representing the current value of 
        //the string object.
        return msg.c_str();
    }
};

class division_by_zero : public std::exception{
private:
    int val;

public:

    /**************************************************************************/
    /*!
        \brief
        Non-default constructor for when a division by 0 occurs and this 
        function is thrown with the param containing the value.

        \param value
        Represents the numerator of the division.

    */
    /**************************************************************************/
    division_by_zero(int const& value) : val(value) {}


    /**************************************************************************/
    /*!
        \brief
        Virtual const char pointer as the return. For the division by zero 
        error. When this function is called, it returns a message to explain to
        the user of the type of error that was caught, rather than vague abort 
        or so message.

        \param msg
        The string message to be sent when an error is caught and the function
        is called to explain to the user, the type of fault.

    */
    /**************************************************************************/
    virtual const char* what() const noexcept { 
        static std::string msg;
        msg = ".\n\nException was thrown: ";
        msg += "Division by zero: ";
        msg += std::to_string(val);
        msg += " / 0!\n";
        return msg.c_str();
    }
};


/****************************************************************************/
/*!
    \brief
    Tests if the first denominator can be divided by the numerator. Prints the
    results if successful, otherwise, throws a division_by_zero error 
    containing the numerator and prints the error type message.

    \param numerator
    Numerator for division.

    \param denominator
    Denominator for division.

    \param divide1
    Is a function pointer of int, int, int& params which returns a bool.

    \param value
    Contains the value of the division, 0 if unsuccessful, >1 if successful.

    \param status
    Bool for the outcome of the divide1, successful or unsuccessful division.

    \param se
    The sequence error name for division by zero.
*/
/****************************************************************************/
template <typename T>
void test1(int numerator, int denominator, T divide1) {
    std::cout<<"Calling function #1";
    try {
        int value{};
        //divide1 function in main
        bool status = divide1(numerator, denominator, value);
        if (!status) 
            throw division_by_zero{numerator};
        std::cout << "; result: " << value <<".\n";
    } 
    catch(division_by_zero const& se){
        std::cout << se.what() << "\n";
        exit(EXIT_SUCCESS);
    }     
}


/****************************************************************************/
/*!
    \brief
    Tests if the second denominator can be divided by the numerator. Prints the
    results if successful, otherwise, throws a division_by_zero error 
    containing the numerator and prints the error type message.

    \param numerator
    Numerator for division.

    \param denominator
    Denominator for division.

    \param divide2
    Is a function pointer of int, int params which returns a pair of bool and 
    int.

    \param res
    Contains the pair of bool and int values of the division. If bool is 0 it 
    is unsuccessful, >1 if successful. int contains the value of successful 
    division

    \param se
    The sequence error name for division by zero.
*/
/****************************************************************************/
template <typename T>
void test2(int numerator, int denominator, T divide2) {
    std::cout << "Calling function #2";
    try {
        std::pair<bool, int> res = divide2(numerator, denominator);
        if (!res.first) 
            throw division_by_zero{numerator};
        std::cout << "; result: " << res.second << ".\n";
    } 
    catch(division_by_zero const& se){
        std::cout << se.what() << "\n";
        exit(EXIT_SUCCESS);
    }     
}


/****************************************************************************/
/*!
    \brief
    Tests if the third denominator can be divided by the numerator. Prints the
    results if successful, otherwise, throws a division_by_zero error 
    containing the numerator and prints the error type message.

    \param numerator
    Numerator for division.

    \param denominator
    Denominator for division.

    \param divide3
    Is a function pointer of int, int params which returns an int of the result.
    Returns calculated value and uses global variable errno to indicate whether 
    result is valid.

    \param value
    Contains the result of the divide3 function pointer.

    \param se
    The sequence error name for division by zero.
*/
/****************************************************************************/
template <typename T>
void test3(int numerator, int denominator, T divide3) {
    std::cout << "Calling function #3";
    try {
        int value = divide3(numerator, denominator);
        if (!errno) 
            throw division_by_zero{numerator};
        std::cout << "; result: " << value << ".\n";
    } 
    catch(division_by_zero const& se){
        std::cout << se.what() << "\n";
        exit(EXIT_SUCCESS);
    }     
}


/****************************************************************************/
/*!
    \brief
    Tests if the fourth denominator can be divided by the numerator. Prints the
    results if successful, otherwise, throws a division_by_zero error 
    containing the numerator and prints the error type message.

    \param numerator
    Numerator for division.

    \param denominator
    Denominator for division.

    \param divide4
    Is a function pointer of int, int params which returns an int of the result.
    Returns calculated value and reserves a specific calculated value to 
    indicate error.

    \param value
    Contains the result of the divide4 function pointer.

    \param se
    The sequence error name for division by zero.
*/
/****************************************************************************/
template <typename T>
void test4(int numerator, int denominator, T divide4) {
    std::cout << "Calling function #4";
    try {
        int value = divide4(numerator, denominator);
        if (value < 0) 
            throw division_by_zero{numerator};
        std::cout << "; result: " << value << ".\n";
    } 
    catch(division_by_zero const& se) {
        std::cout << se.what() << "\n";
        exit(EXIT_SUCCESS);
    }     
}


/****************************************************************************/
/*!
    \brief
    Tests if the fifth denominator can be divided by the numerator. Prints the
    results if successful, otherwise, throws a division_by_zero error 
    containing the numerator and prints the error type message.

    \param numerator
    Numerator for division.

    \param denominator
    Denominator for division.

    \param divide5
    Is a function pointer of int, int params which returns an int of the result.
    Returns calculated value and indicates an error by throwing an exception.

    \param value
    Contains the result of the divide5 function pointer.

    \param se
    The sequence error name for division by zero.
*/
/****************************************************************************/
template <typename T>
void test5 (int numerator, int denominator, T divide5) {
    std::cout << "Calling function #5";
    try {
        int value = divide5(numerator, denominator);
            std::cout << "; result: " << value << ".\n";
    } 
    catch(division_by_zero const& se){
        std::cout << se.what() << "\n";
        exit(EXIT_SUCCESS);
    }     
}
} // namespace hlp2 end
