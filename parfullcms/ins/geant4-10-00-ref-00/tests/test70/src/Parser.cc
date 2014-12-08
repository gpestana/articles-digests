#include "Parser.hh"
#include <iomanip>

using namespace std;

inline bool MATCH(const char *a, const char *b)
{
    return strcmp(a,b)==0;
}

Parser* Parser::fpInstance(0);

Parser::Parser()
{
    //    G4cout << "############ NEW PARSE ##########" << G4endl;
    fpInstance = this;
    fOptionsWereSetup = false;
    fMaxMarkerLength = 0;
    fMaxOptionNameLength = 0;
    AddCommand("--help", WithoutOption, "Print this help");
    AddCommand("-h", WithoutOption, "Print this help");
    AddCommand("&", WithoutOption);

    fVerbose = 0;
}

Parser* Parser::GetParser()
{
    if(!fpInstance) new Parser;
    return fpInstance;
}

Parser::~Parser()
{
    std::map<G4String, Command*>::iterator it = fCommandMap.begin();
    for(;it!=fCommandMap.end() ; it++)
    {
        if(it->second)
            delete it->second;
    }
}

void Parser::DeleteInstance()
{
    if(fpInstance)
    {
        delete fpInstance;
        fpInstance = 0;
    }
}

Command::Command(CommandType commandType, const G4String& description, const G4String& optionName)
{
    fType = commandType;
    fDescription = description;
    fOptionName = optionName;
    fOption = "";
    fActive = false;
}

int Parser::Parse(int& argc, char **argv)
{
    //    G4cout << "Parse " << G4endl;
    static char null[1] = { "" };
    int firstArgc = argc;

    for(int i = 1 ; i < firstArgc ; i++)
    {
        Command* command = FindCommand(argv[i]);
        if(command == 0) continue;

        if(fVerbose)
            G4cout <<"Command : "<< argv[i] << G4endl;

        fOptionsWereSetup = true;
        command->fActive = true;
        argv[i] = null;

        if(command->fType == WithOption)
        {
            if(fVerbose)
                G4cout <<"WithOption"<<G4endl;

            command->fOption = (const char*) strdup(argv[i+1]);
            argv[i+1] = null;
            i++;
        }
        else if(command->fType == OptionNotCompulsory)
        {
            if(fVerbose)
                G4cout <<"OptionNotCompulsory"<<G4endl;

            if(i+1 < firstArgc)
            {
                G4String buffer = (const char*) strdup(argv[i+1]);

                if(buffer.empty() == false)
                {
                    if(buffer.at(0) != '-' && buffer.at(0) != '&' && buffer.at(0) != '>' && buffer.at(0) != '|')
                    {
                        if(fVerbose)
                            G4cout << "facultative option is : " << buffer << G4endl;

                        command->fOption = (const char*) strdup(argv[i+1]);
                        argv[i+1] = null;
                        i++;
                        continue;
                    }
                }
            }

            if(fVerbose)
                G4cout << "Option not set" << G4endl;

            command->fOption = "";
        }
    }
    CorrectRemainingOptions(argc,argv);

    Command* commandLine(0);
    if((commandLine = GetCommandIfActive("--help")))
    {
        G4cout << "Usage : " << argv[0] << " [OPTIONS]" << G4endl;
        PrintHelp();
        return 1;
    }
    else if((commandLine = GetCommandIfActive("-h")))
    {
        G4cout << "Usage : " << argv[0] << " [OPTIONS]" << G4endl;
        PrintHelp();
        return 1;
    }

    return 0;
}

void Parser::PrintHelp()
{    
    std::map<G4String, Command*>::iterator it;

    int maxFieldLength = fMaxMarkerLength+fMaxOptionNameLength+4;

    G4cout << "Options: " << G4endl;

    for(it = fCommandMap.begin(); it!=fCommandMap.end();it++)
    {
        Command* command = it ->second;
        if(command)
        {
            G4cout << setw(maxFieldLength) << left;

            G4String toPrint = it->first ;

            if(toPrint  == "&")
            {
                continue;
            }
            else if(toPrint  == "-h") continue;
            else if(toPrint  == "--help")
            {
                toPrint += ", -h" ;
            }

            if(command->GetOptionName() != "")
            {
                toPrint += " \""  +command->GetOptionName() +"\"" ;
            }

            G4cout << toPrint  ;

            G4cout << command->GetDescription() <<G4endl;
        }
    }
}

void Parser::CorrectRemainingOptions(int& argc, char **argv)
{
    // remove handled arguments from argument array
    int j = 0;
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], ""))
        {
            argv[j] = argv[i];
            j++;
        }
    }
    argc = j;
}

void Parser::AddCommand(const G4String& marker, CommandType type,
                        const G4String& description, const G4String& optionName)
{
    //   G4cout << "Add command : "<< marker << G4endl;
    Command* command = new Command(type, description, optionName);
    if((int) marker.length() > fMaxMarkerLength) fMaxMarkerLength = marker.length() ;
    if((int) optionName.length() > fMaxOptionNameLength) fMaxOptionNameLength = optionName.length() ;
    fCommandMap.insert(make_pair(marker,command));
}

Command* Parser::FindCommand(const G4String& marker)
{
    std::map<G4String, Command*>::iterator it = fCommandMap.find(marker);
    if(it == fCommandMap.end())
    {
        //        G4cerr << "command not found" << G4endl;
        return 0;
    }
    //    if(it->second->fActive)
    return it->second;
    //    return 0;
}

Command* Parser::GetCommandIfActive(const G4String &marker)
{
    Command* command = FindCommand(marker);
    if(command)
    {
        //	G4cout << "Command found : "<< marker << G4endl;

        if(command->fActive)
        {

            //	    G4cout << "Command Active" << G4endl;
            return command;
        }
        //	else
        //		G4cout <<"Command not active" << G4endl;
    }
    else
    {
        G4cerr << "You try to retrieve a command that was not registered : "  << marker << G4endl;
        exit(-1);
    }
    return 0;
}
