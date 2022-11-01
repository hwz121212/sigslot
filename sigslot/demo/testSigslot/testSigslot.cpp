

#include "stdafx.h"
#include "sigslot.h"

class Sender     
{   
public:   
   
    sigslot::signal2< std::string , int > SignalDanger;   
    void SayHelp()   
    {   
	    printf("A : ~~ Help~~ \n");
        SignalDanger("Help!", 1);    
    }   
};  

class Receiver : public sigslot::has_slots<>
{
public:
    void OnDanger(std::string message, int time)
    {
        printf("B : I heard something say \"%s\" at %d!\n", message.c_str(), time);
    }
}; 

int main(int argc, char* argv[])
{

	Sender sender;
	Receiver receiver;
	sender.SignalDanger.connect(&receiver, &Receiver::OnDanger);

	sender.SayHelp();

	return 0;
}

