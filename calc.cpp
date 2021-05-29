/*
 Nazat Hossain
 */
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;
string input;
bool inputcheck(const string& input); //prototypes
void calculation(string input);
struct node {
    int value;
    node* next;
};
class stack{
public:
    stack(); //constructor
    void push(int add); //method to add a value to stack
    int pop(); //method to remove top value of stack
    void Print(); //method to print the stack
    ~stack(); //deconstructor
    typedef struct node* nodePtr;
    nodePtr tail;
    nodePtr top;
    nodePtr temp;
};

stack::stack() //initialise
{
    tail = NULL;
    top = NULL;
    temp = NULL;
}

stack::~stack()
{
    tail = NULL; //resets all values to NULL
    top = NULL;
    temp = NULL;
    delete tail; //freeing up allcocated memory
    delete top;
    delete temp;
    cout<<"Thank you for using my RPN Calculator!"<<endl;
}

void stack::push(int add) //method to add a value onto the stack
{
    nodePtr newNode = new node;
    newNode->next = NULL;
    newNode->value = add;
    if (tail != NULL) //if stack is not empty
    {
        top = tail;
        while(top->next != NULL)
        {
            top = top->next;
        }
        top->next = newNode;
    }
    else //if stack is empty
    {
        tail = newNode;
    }
}

int stack::pop() //method to remove the top value from the stack and return the value
{
    nodePtr deletePtr = NULL;
    temp = tail;
    top = tail;
    while(top->next != NULL)
    {
        temp = top;
        top = top->next;
    }
    try {
    if (tail->next == NULL) //check for if stack is empty
    {
        delete deletePtr;
        throw 1;
    }
    }
        catch(int x)
        {
            cout <<"ERROR CODE : " << x <<  ". The stack was empty" <<endl;
        }
        //pops top value of stack
        deletePtr = top;
        top = top->next;
        temp->next = top;
        return deletePtr->value;
}

void stack::Print() //method to print the stack
{
    top = tail;
    while(top != NULL) //loop to run through the stack
    {
        cout<< top->value<<endl;
        top = top->next;
    }
}

class stack mainCalc; //creates object of mainCalc
int main()
{
    cout << "This is an RPN calculator." << endl;
    cout << "It recognizes integers, the operators + and -" << endl;
    cout << "'stack' can be used to print all elements and 'quit' to exit" << endl;
    while(true)
    {
        cout << ">";
        cin >> input;
        cout << "In : " + input << endl;
        int num;
        if(istringstream(input) >> num) //checks if input is an integer
        {
            mainCalc.push(num); //integer is passed as an argument to push method where it is added to the stack
        }
        else if(inputcheck(input)) //checks if input is an operator
        {
            calculation(input);
        }
        else if(input == "quit") //exit
        {
            return 0;
        }
        else if(input == "stack") //prints out the stack by calling the print method
        {
            mainCalc.Print();
        }
        else
        {
            cout << "Invalid input" << endl; //if the user inputs anything other than an integer or operator
        }
    }
}

bool inputcheck(const string& input) //method to check if the input is an operator
{
    string ops[] = {"+","-"};
    for(int i = 0; i < 2; i++)
    {
        if(input == ops[i])
        {
            return true;
        }
    }
    return false;
}
void calculation(string input) //performs the operations
{
    int firstVar, secondVar, result;
    firstVar = mainCalc.pop(); //stores first operator into firstVar
    secondVar = mainCalc.pop(); //storess second operator into secondVar
    if (input == "+")
    {
        result = firstVar + secondVar;
    }
    else
    {
        result = firstVar - secondVar;
    }
    cout << result << endl;
    mainCalc.push(result);
}

