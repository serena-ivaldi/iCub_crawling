#include "CrawlManagerModule.h"
#include <yarp/os/Os.h>
#include <stdio.h>
#include <string>

using namespace std;

#define DEBUG 1

char ESC=27; // don't know what is for


//==========================================================//
// UPDATE MODULE
//==========================================================//
bool CrawlManagerModule::updateModule()
{
    if(com==9)  //SI: this will be replaced by something better (TODO)
        return false;

    //SI: long term: this will be replaced by a GUI (TODO)
    
    if(commandOnTerminal==3)
    {
        cout<<"\n\n";
        cout << "**********************************"<<endl;
        cout << "              MENU                "<<endl;
        cout << "**********************************"<<endl;
        cout << "Please specify the task" << endl;
        cout << "(1) Go to init pos" << endl;
        cout << "(2) Crawl" << endl;
        cout << "(3) Faster" << endl;
        cout << "(4) Slower" << endl;
        cout << "(5) Turn right" << endl;
        cout << "(6) Turn left" << endl;
        cout << "(8) Check connections"<<endl;
        cout << "(9) Stop" << endl;
        cout << "(0) Toggle verbosity"<<endl;
        cout << "**********************************"<<endl;
        
        cout<<"type command on keyboard ==> "<< endl;
        
        commandOnTerminal=0;
    }
    
    return true;
}

//==========================================================//
// GET PERIOD
//==========================================================//
double CrawlManagerModule::getPeriod()
{
    return 2.0;
}

//==========================================================//
// CLOSE
//==========================================================//
bool CrawlManagerModule::close()
{
    cout<< " ++ CRAWL manager module closing..."<<endl;
    for(int i=0;i<6;i++)
        if(connected_part[i]==true)
        {
            cout<<"   ++ Closing ports for part "<<i<<endl;
            parts_port[i].close();
            check_port[i].close();
        }
    cout<<"   ++ Closing port for commands "<<endl;
    commandPort.close();
    return true;
}


//==========================================================//
// CHECK CONNECTIONS
//==========================================================//
int CrawlManagerModule::checkConnections()
{
    bool mustTryReconnection = false;
    int returnStatus=CONNECTION_ALL_GOOD;
    
    cout<<"+++ Connection status +++ "<<endl;
    for(int i=0;i<nbParts;i++)
    {
        cout<<part_names[i]<<"   ";
        if(connected_part[i] == true)
            cout<<" connected"<<endl;
        else
        {
            cout<<" NOT connected"<<endl;
            mustTryReconnection = true;
        }
    }
    

    // we try to reconnect to all the ports of the crawl Generators
    cout<<"+++ Checking connections +++ \n"<<endl;
    
    for(int i=0;i<nbParts;i++)
    {
        char tmp1[255],tmp2[255];
        sprintf(tmp1,"/%s/%s/parameters/in",generatorsName.c_str(),part_names[i].c_str());
            
        /////////////////////////////////////////////////////
        // check if the part is active and connect///////////
        /////////////////////////////////////////////////////
        Contact query = Network::queryName(tmp1);
            
        if((connected_part[i] == true)&&(query.isValid()))
        {
            //was connected before (connected==true) and is still alive
            cout<<"[OK] ["<<part_names[i]<<"] is connected and still alive   "<<endl;
        }
        else if((connected_part[i] == true)&&(!query.isValid()))
        {
            // was connected before but query says the port is dead
            cout<<"[NO] ["<<part_names[i]<<"]  is no longer alive!! "<<endl;
            connected_part[i] = false;
            returnStatus=CONNECTION_LOST_CONNECTION;
        }
        else
        {
            //it was not connected before..
                
            if(query.isValid())
            {
                //the generator is alive! horray!!!
                
                cout<<"[  ] ["<<part_names[i]<<"] attempting connection with the generator ..."<<endl;
                cout << "     ... found the generator on port: " << tmp1 << endl;
                
                sprintf(tmp2,"/%s/%s/out",moduleName.c_str(),part_names[i].c_str());
                cout << "     ... creating local port: " << tmp2 << endl;
                
                bool ok = parts_port[i].open(tmp2);
                if(!ok)
                {
                    printf("    ... unable to open a port %s   [ERROR] \n",tmp2);
                    return CONNECTION_PORT_ERROR;
                }
                
                cout << "     ... connecting " << tmp2 << " with "<<tmp1<<endl;
                ok = Network::connect(tmp2,tmp1);
                if(!ok)
                {
                    printf("    ... unable to connect %s with %s     [ERROR] \n",tmp2,tmp1);
                    return CONNECTION_PORT_ERROR;
                }
                
                sprintf(tmp1, "/%s/%s/status/in", moduleName.c_str(),part_names[i].c_str());
                sprintf(tmp2, "/%s/status_for_manager/out", part_names[i].c_str());
                
                cout << "     ... creating local port: " << tmp1 << endl;
                ok = check_port[i].open(tmp1);
                if(!ok)
                {
                    printf("    ... unable to open %s\n",tmp1);
                    return CONNECTION_PORT_ERROR;
                }
                
                cout << "     ... connecting " << tmp2 << " with "<<tmp1<<endl;
                ok = Network::connect(tmp2,tmp1);
                if(!ok)
                {
                    printf("    ... unable to connect %s with %s \n",tmp2,tmp1);
                    return CONNECTION_PORT_ERROR;
                }
                
                connected_part[i] = true;
                cout<<"[OK] ["<<part_names[i]<<"] is now connected to the generator!   "<<endl;
                
            }
            else
            {
                //the generator is not alive... booooo
                // nothing changes
                cout<<"[NO] ["<<part_names[i]<<"] is not running - please start its generator! "<<endl;
                returnStatus=CONNECTION_MISSING;
            }
            
        }
    }
    
    return returnStatus;
    
}

//==========================================================//
//  RESPOND
//==========================================================//
/*
 This function switches between behaviors
 It takes the input command from keyboard -> there is the attachTerminal()
 and calls the proper action for each command
*/
bool CrawlManagerModule::respond(const Bottle& command, Bottle& reply)
{
  com = command.get(0).asInt();
  cout << "received command == " << com << endl;
  
   switch(com)
    {
            
        case 0: /// toggling verbosity level
            
            if(verbosity_debug==0)
            {
                verbosity_debug=1;
                reply.addString("verbosity from 0 to 1 (some printing)");
            }
            else if(verbosity_debug==1)
            {
                verbosity_debug=2;
                reply.addString("verbosity from 1 to 2 (all printing)");
            }
            else if(verbosity_debug==2)
            {
                verbosity_debug=0;
                reply.addString("verbosity from 2 to 0 (no printing)");
            }
            else
            {
                reply.addString("nothing done");
            }
            break;
            
            
        case 1: /// - on all fours
        
			InitPosition();
            reply.addString("going to init pos");
            
            break;
            
        case 2:  ///- crawl (straight)
        
			Crawl();
            reply.addString("crawling");
            
            break;
                
        case 3: ///- crawl faster
            
            Crawl(turnAngle,STANCE_INDENT);
            reply.addString("crawling faster");
            
            break;
            
        case 4:///- crawl slower
            
            Crawl(turnAngle, -STANCE_INDENT);
            reply.addString("crawling slower");
            
            break;
            
        case 5: ///- turn to the right
            
			//Crawl(-MAX_TURN_ANGLE);
			Crawl(turnAngle-TURN_INDENT, 0);
            reply.addString("turning right");
            
            break;
            
        case 6:///- turn to the left

			//Crawl(MAX_TURN_ANGLE);
            Crawl(turnAngle+TURN_INDENT,0);
            reply.addString("turning left");
            
            break;
            


        //=========added by Seb=========
		case SEB_TURN_COMMAND: ///- turn to avoid obstacles 
        {
            double angle = command.get(1).asDouble();
            cout << "angle : " << angle << endl;

			Crawl(angle);
            
			reply.addString("turning\n");
			STATE = CRAWL;

            break;
        }

		case HEAD_ROT_COMMAND :
		{
			double pitchAngle = command.get(1).asDouble();
			double yawAngle = command.get(2).asDouble();

			HeadControl(pitchAngle, yawAngle);
            reply.addString("rotate head");
			
			break;
		}
        
		case REACH_COMMAND: ///- reach for a mark on the ground
		{
			Reach(command.get(1).asList());	

            reply.addString("reaching\n");
			STATE = REACH;

            break;
		}                
		//=========END added by Seb=========

		case 9: /// - emergency stop  (will stop the module)
                
            crawl_left_parameters[9][1]=turnAngle; //???? SI: not safe, to be changed (TODO)
            
            //if the robot is not crawling, we go to an intermediate position
            //otherwise, we do nothing
            if(STATE==CRAWL)
            {
                int side=0;
                while(side==0) side=getSwingingArm();  //???? SI
                
                if(side==LEFT_ARM)
                {
                    for(int i=0;i<nbParts;i++)
                        if(connected_part[i]) sendCommand(i, crawl_left_parameters);
                    Time::delay(1.0);
                }
                
                if(side==RIGHT_ARM)
                {
                    for(int i=0;i<nbParts;i++)
                        if(connected_part[i]) sendCommand(i, crawl_right_parameters);
                    Time::delay(1.0);
                }
            }
            
            reply.addString("Closing... ");
            
            crawl_left_parameters[9][1]=0.0; //???? SI: not safe, to be changed (TODO)
            
            break;
            
        case 8: //SI: check connections (to reconnect in case)
            
            if(checkConnections()==CONNECTION_ALL_GOOD)
                reply.addString("all connections with generators are good");
            else
                reply.addString("unable to connect to some generators, error");
            
            break;
            
            
        default:
            
            reply.addString("Command unknown");
            break;
            
        }
    
    commandOnTerminal++;
        
    return true;
       
}





//==========================================================//
//  CONFIGURE
//==========================================================//
//CT(22-3-2011) change open(Searchable &s) for configure(yarp::os::ResourceFinder &rf)
bool CrawlManagerModule::configure(yarp::os::ResourceFinder &rf)
{
    Time::turboBoost();
    
    moduleRate=0.0;
    verbosity_debug=-1;
    
    part_names[0]="left_arm";
    part_names[1]="right_arm";
    part_names[2]="left_leg";
    part_names[3]="right_leg";
    part_names[4]="torso";
    part_names[5]="head";
    
    STATE = NOT_SET;
    turnAngle=0;
    commandOnTerminal=3;
    
    vector<double> crawl_ampl;
    vector<double> crawl_target;
    vector<double> init_ampl;
    vector<double> init_target;
    
		
    // Process all parameters from both command-line and .ini file
    // SI: this has been re-written
    
    if(rf.check("module"))
    {
        Bottle& bot = rf.findGroup("module");
        
        moduleName = bot.find("module_name").asString();
        if(moduleName == "")
        {
            printf("%c[1m",ESC);
            printf("***ERROR*** missing module_name -> setting default\n");
            printf("%c[0m",ESC);
            moduleName="crawlManager";
        }
        
        generatorsName = bot.find("generators_name").asString();
        if(generatorsName == "")
        {
            printf("%c[1m",ESC);
            printf("***ERROR*** missing generators_name -> setting default\n");
            printf("%c[0m",ESC);
            generatorsName="crawlGenerator";
        }
        
        moduleRate = bot.find("module_rate").asDouble();
        if(moduleRate == 0.0)
        {
            printf("%c[1m",ESC);
            printf("***ERROR*** missing moduleRate -> setting default\n");
            printf("%c[0m",ESC);
            moduleRate=1.0;
        }
        
        verbosity_debug = bot.find("verbosity").asInt();
        if(verbosity_debug == -1)
        {
            printf("%c[1m",ESC);
            printf("***ERROR*** missing moduleRate -> setting default\n");
            printf("%c[0m",ESC);
            verbosity_debug=2;
        }
        
    }
    else
    {
        printf("%c[1m",ESC);
        printf("***ERROR*** NO MODEL PARAMETERS \n");
        printf("%c[0m",ESC);
        
        cout<<"Could not find module parameters in configuration file!"<<endl
            <<"Setting default values"<<endl;
        
        moduleName="crawlManager";
        moduleRate=1.0;
        verbosity_debug=2;
        generatorsName="crawlGenerator";
    }
    

    cout<<"+++++++++++++++ PARAMS +++++++++++++++++++"<<endl;
    cout<<"Manager module name   = "<<moduleName<<endl;
    cout<<"Manager rate          = "<<moduleRate<<endl;
    cout<<"Generator module name = "<<generatorsName<<endl;
    cout<<"Verbosity             = "<<verbosity_debug<<endl;
    cout<<"++++++++++++++++++++++++++++++++++++++++++"<<endl;



    //**** CHECKING CONNECTIONS ****
    


    //we connect to the ports of the crawl Generators
    for(int i=0;i<nbParts;i++)
    {
        char tmp1[255],tmp2[255];
        sprintf(tmp1,"/%s/%s/parameters/in",generatorsName.c_str(),part_names[i].c_str());

        /////////////////////////////////////////////////////
        // check if the part is active and connect///////////
        /////////////////////////////////////////////////////
        Contact query = Network::queryName(tmp1);
        if(query.isValid())
        {
            cout << "found part " << tmp1 << " ... connecting" << endl;
            sprintf(tmp2,"/%s/%s/out",moduleName.c_str(),part_names[i].c_str());
            bool ok = parts_port[i].open(tmp2);
            if(!ok)
            {
                printf("unable to open %s\n",tmp2);
                return false;
            }
            ok = Network::connect(tmp2,tmp1);
            if(!ok)
            {
                printf("unable to connect %s with %s\n",tmp2,tmp1);
                return false;
            }
                    
            connected_part[i] = true; //the part i is connected
            
            sprintf(tmp1, "/%s/%s/status/in", moduleName.c_str(),part_names[i].c_str());
            sprintf(tmp2, "/%s/status_for_manager/out", part_names[i].c_str());
            ok = check_port[i].open(tmp1);
            if(!ok)
            {
                printf("unable to open %s\n",tmp1);
                return false;
            }
            ok = Network::connect(tmp2,tmp1);
            if(!ok)
            { 
                printf("unable to connect %s with %s\n",tmp2,tmp1);
                return false;
            }
        }
        else
		{
        	connected_part[i] = false;
        	printf("%c[1m",ESC); 
			printf("***ERROR*** PART %s NOT DETECTED \n", part_names[i].c_str());
			printf("%c[0m",ESC); 
		}
			  
        
        //**** GETTING PARAMETERS FOR THE GENERATORS ****
            
        ///////we get the parameters from the config files
        //CTmodified: if(options.check(part_names[i].c_str()))
		if(rf.check(part_names[i].c_str()))
        {
            Bottle& bot = rf.findGroup(part_names[i].c_str());
            
            Bottle& bot1=bot.findGroup("nbJoints");
            nbDOFs[i] =bot1.get(1).asInt();
            printf("nbJoints %d\n", nbDOFs[i]);

			om_swing.push_back(bot.find("omSwing").asDouble());
			om_stance.push_back(bot.find("omStance").asDouble());
            
            Bottle& bot2 = bot.findGroup("mu_crawl");
            Bottle& bot3 = bot.findGroup("setPoints_crawl");
            if(bot2.isNull() || bot3.isNull() || bot2.size()<nbDOFs[i]+1 || bot3.size()<nbDOFs[i]+1)
            {
                printf("please specify crawl config for %s\n",part_names[i].c_str());
                return false;
            }
                
            for(int j=0;j<nbDOFs[i];j++)
            {
                crawl_ampl.push_back(bot2.get(j+1).asDouble());
                crawl_target.push_back(bot3.get(j+1).asDouble());
            }

            crawl_parameters.push_back(crawl_ampl);
            crawl_parameters.push_back(crawl_target);
            
            crawl_ampl.clear();
            crawl_target.clear();
            
            Bottle& bot6 = bot.findGroup("mu_left_crawl");
            Bottle& bot7 = bot.findGroup("setPoints_left_crawl");
            if(bot6.isNull() || bot7.isNull() || bot6.size()<nbDOFs[i]+1 || bot7.size()<nbDOFs[i]+1)
            {
                printf("please specify left crawl config for %s\n",part_names[i].c_str());
				return false;
            }
                
            for(int j=0;j<nbDOFs[i];j++)
            {
                crawl_ampl.push_back(bot6.get(j+1).asDouble());
                crawl_target.push_back(bot7.get(j+1).asDouble());
            }

            crawl_left_parameters.push_back(crawl_ampl);
            crawl_left_parameters.push_back(crawl_target);
            
            crawl_ampl.clear();
            crawl_target.clear();
            
            Bottle& bot8 = bot.findGroup("mu_right_crawl");
            Bottle& bot9 = bot.findGroup("setPoints_right_crawl");
            if(bot8.isNull() || bot9.isNull() || bot8.size()<nbDOFs[i]+1 || bot9.size()<nbDOFs[i]+1)
            {
                printf("please specify right crawl config for %s\n",part_names[i].c_str());
                return false;
            }
                
            for(int j=0;j<nbDOFs[i];j++)
            {
                crawl_ampl.push_back(bot8.get(j+1).asDouble());
                crawl_target.push_back(bot9.get(j+1).asDouble());
            }

            crawl_right_parameters.push_back(crawl_ampl);
            crawl_right_parameters.push_back(crawl_target);
                                                    
            crawl_ampl.clear();
            crawl_target.clear();

            Bottle& bot4 = bot.findGroup("mu_init");
            Bottle& bot5 = bot.findGroup("setPoints_init");
            if(bot4.isNull() || bot5.isNull() || bot4.size()<nbDOFs[i]+1 || bot5.size()<nbDOFs[i]+1)
            {
                printf("please specify init config for %s\n",part_names[i].c_str());
                return false;
            }
            for(int j=0;j<nbDOFs[i];j++)
            {
                init_ampl.push_back(bot4.get(j+1).asDouble());
                init_target.push_back(bot5.get(j+1).asDouble());
            }
            init_parameters.push_back(init_ampl); 
            init_parameters.push_back(init_target); 

            init_ampl.clear();
            init_target.clear();

        
            printf("crawl parameters for part %s\n", part_names[i].c_str());
            printf("amplitudes ( ");
            for(int j=0; j<nbDOFs[i]; j++) 
                printf("%f ", crawl_parameters[2*i][j]);
            printf(")\ntargets (");
            for(int j=0; j<nbDOFs[i]; j++) 
                printf("%f ", crawl_parameters[2*i+1][j]);
            printf(")\n", om_stance[i], om_swing[i]); 
            
            printf("crawl left parameters for part %s\n", part_names[i].c_str());
            printf("amplitudes ( ");
            for(int j=0; j<nbDOFs[i]; j++) 
                printf("%f ", crawl_left_parameters[2*i][j]);
            printf(")\ntargets (");
            for(int j=0; j<nbDOFs[i]; j++) 
                printf("%f ", crawl_left_parameters[2*i+1][j]);
            printf(")\n", om_stance[i], om_swing[i]); 
            
            printf("crawl right parameters for part %s\n", part_names[i].c_str());
            printf("amplitudes ( ");
            for(int j=0; j<nbDOFs[i]; j++) 
                printf("%f ", crawl_right_parameters[2*i][j]);
            printf(")\ntargets (");
            for(int j=0; j<nbDOFs[i]; j++) 
                printf("%f ", crawl_right_parameters[2*i+1][j]);
            printf(")\n", om_stance[i], om_swing[i]); 
            
            printf("init parameters for part %s\n", part_names[i].c_str());
            printf("amplitudes ( ");
            for(int j=0; j<nbDOFs[i]; j++) 
                printf("%f ", init_parameters[2*i][j]);
            printf(")\ntargets (");
            for(int j=0; j<nbDOFs[i]; j++) 
                printf("%f ", init_parameters[2*i+1][j]);
            printf(")\n", om_stance[i], om_swing[i]); 
        }
        else
        {
			printf("please specify config for %s\n",part_names[i].c_str());
			cin.get();
			return false;
        }
    }
    
	//=========START added by Seb=========
	commandPort.open(COMMAND_PORT_NAME);
		attachTerminal();
	printf("Attaching CommandPort to the terminal");

	//the constructor of bufferedport is already doing the attach right?? How can I change the !attach question to veryfy this??
    /*if(!(attach(commandPort,true)))
    {
        cout << "WARNING : port not attached to respond function" << endl;
    }*/
	//=========END added by Seb=========

      
    return true;

}


//==========================================================//
//  GET SWINGING ARM / SIDE
//==========================================================//
///This function returns which arm is in the swinging phase according to the cpgs info 
///(1= left arm, -1= right arm, 0= no info or not applicable)
int CrawlManagerModule::getSwingingArm()
{    
    int side=0;
    double y_speed[4];
    bool swing[4]={false,false,false,false};
    
    for(int i=0; i<4; i++)
    {
        Bottle *command = check_port[i].read(false);
        if(command!=NULL)
        {
            printf("getting info from the generators\n");
            y_speed[i] = command->get(0).asDouble();
            y_speed[i]>0.0 ? swing[i] = false : swing[i] = true;
        }
        else printf("no info\n");
    }
    
    printf("y_speed %f %f %f %f\n", 
                            y_speed[0], y_speed[1], y_speed[2], y_speed[3]);
    
    if(swing[0] || swing[3] || !swing[1] ||!swing[2]) side = LEFT_ARM;
    if(!swing[0] || !swing[3] || swing[1] ||swing[2]) side = RIGHT_ARM;

    return side; 
}


//==========================================================//
//  SEND COMMAND TO GENERATORS
//==========================================================//
/*
 This function sends the command parameters to the different generator.
 i= the index of the body part
 params= the parameters of the generator: amplitude, target, stance, swing, angle
 */
void CrawlManagerModule::sendCommand(int i, vector<vector<double> > params)
{
    Bottle& paramBot = parts_port[i].prepare();
    paramBot.clear();
    for(int j=0;j<nbDOFs[i];j++)
    {
        paramBot.addDouble(params[2*i][j]); 
        paramBot.addDouble(params[2*i+1][j]);                               
    }
    paramBot.addDouble(om_stance[i]);
    paramBot.addDouble(om_swing[i]);
    paramBot.addDouble(turnAngle);
    parts_port[i].write();
                            
    if(verbosity_debug>1)
    {
        printf("SENDING COMMAND TO PART %s:\n", part_names[i].c_str());
        printf("amplitudes ( ");
        for(int j=0; j<nbDOFs[i]; j++)
            printf("%f ", params[2*i][j]);

        printf(")\ntargets (");
        for(int j=0; j<nbDOFs[i]; j++)
            printf("%f ", params[2*i+1][j]);
        
        printf(")\n om_stance %f, om_swing %f, turnAngle %f\n\n", om_stance[i], om_swing[i], turnAngle);
    }
}


//==========================================================//
//  INIT POSITION
//==========================================================//
void CrawlManagerModule::InitPosition(void)
{
    //if the robot crawls, we need to check if it safe before going on all fours
    if(STATE==CRAWL)
    {
        //if it turns (turnAngle!=0), it should go back to the initial position while crawling
        if(turnAngle < -0.001)
        {
            while(turnAngle < -0.001)
            {
                turnAngle+=TURN_INDENT;   //SI: to change, since INDENT is bigger than the threshold (TODO)
                crawl_parameters[9][1]=turnAngle;  //SI: ??
                for(int i=0;i<nbParts;i++)
                    if(connected_part[i]) sendCommand(i, crawl_parameters);
                Time::delay(1.0);
            }
        }
        
        if(turnAngle > 0.001)
        {
            while(turnAngle > 0.001)
            {
                turnAngle-=TURN_INDENT; //SI: to change, since INDENT is bigger than the threshold (TODO)
                crawl_parameters[9][1]=turnAngle; // SI: ??
                for(int i=0;i<nbParts;i++)
                    if(connected_part[i]) sendCommand(i, crawl_parameters);
                Time::delay(1.0);
            }
        }
        
        //the robot first goes to an intermediate position before going on all fours
        //the swinging arm is lifted and then put on the ground                    
        int side=0;
        while(side==0) {
        	side=getSwingingArm();
        }
        
        if(verbosity_debug>0) cout << "current swing side : " << side << endl;

        if(side==LEFT_ARM)
        {
            for(int i=0;i<nbParts;i++)
                if(connected_part[i]) sendCommand(i, crawl_left_parameters);
            Time::delay(5.0);
        }
        
        if(side==RIGHT_ARM)
        {
            for(int i=0;i<nbParts;i++)
                if(connected_part[i]) sendCommand(i, crawl_right_parameters);
            Time::delay(5.0);
        }
    }
    
    //we can now send the init position
    //the stance frequency om_stance is reinitialized
    
    if(verbosity_debug>0) cout << "sending the initialisation position "<< endl;
    
    for(int i=0;i<nbParts;i++)
	{
        if(connected_part[i])
		{
			sendCommand(i, init_parameters);
			om_stance[i] = om_swing[i];
		}
	}
    
	STATE = INIT_POS;
}


//==========================================================//
//  CRAWL
//==========================================================//
void CrawlManagerModule::Crawl(double desiredTurnAngle, double stanceIncrement)
{
	if(desiredTurnAngle > MAX_TURN_ANGLE)
	{
		desiredTurnAngle = MAX_TURN_ANGLE;
        printf("Already at MAX TURN ANGLE %4.2f\n", MAX_TURN_ANGLE);  
	}
	else if(desiredTurnAngle < -MAX_TURN_ANGLE)
	{
		desiredTurnAngle = -MAX_TURN_ANGLE;
        printf("Already at MIN TURN ANGLE %4.2f\n", -MAX_TURN_ANGLE);  

	}

	//We have the robot turn incrementally to the desired turn angle.
    if(STATE==CRAWL && desiredTurnAngle != turnAngle)
	{
		if(turnAngle < desiredTurnAngle)
		{
			while(turnAngle <  desiredTurnAngle-TURN_INDENT/2)
			{
				turnAngle+=TURN_INDENT;
				crawl_parameters[9][1]=turnAngle;
				for(int i=0;i<nbParts;i++)
				{
					if(part_names[i] == "head")
					{
						continue;
					}
					if(connected_part[i]) sendCommand(i, crawl_parameters);
				}
				Time::delay(1.0);
			}
		}
    
		if(turnAngle > desiredTurnAngle)
		{
			while(turnAngle > desiredTurnAngle+TURN_INDENT/2)
			{
				turnAngle-=TURN_INDENT;
				crawl_parameters[9][1]=turnAngle;
				for(int i=0;i<nbParts;i++)
				{
					if(part_names[i] == "head")
					{
						continue;
					}
					if(connected_part[i]) sendCommand(i, crawl_parameters);
				}
				Time::delay(1.0);
			}
		}
	}

    //if the robot is not crawling, we go first to an intermediate position
    if(STATE!=CRAWL)
    {
        if(verbosity_debug>0) cout<<"Bringing the robot to an initial configuration for crawling"<<endl;
        
        for(int i=0;i<nbParts;i++)
            if(connected_part[i])
			{
				sendCommand(i, crawl_right_parameters);
			}
        turnAngle=0;
        Time::delay(5.0);
    }
    
    //we can now send the normal crawling parameters
    for(int i=0;i<nbParts;i++)
        if(connected_part[i]) 
		{
            if(part_names[i]!="head") om_stance[i]+=stanceIncrement;
            
			sendCommand(i, crawl_parameters);
		}
    
    STATE = CRAWL;
}


//==========================================================//
//  REACH
//==========================================================//
void CrawlManagerModule::Reach(Bottle *reachingCommand)
{
	printf("command : %s\n",reachingCommand->toString().c_str());
	ConstString reachingPart = reachingCommand->get(0).asString();
	printf( "REACHING WITH PART %s\n", reachingPart.c_str());

	if(STATE!=CRAWL)
    {
		if(reachingPart == "left_arm")
		{
			for(int i=0;i<nbParts;i++)
			{
				if(part_names[i] == "head")
				{
					continue;
				}
				if(connected_part[i]) sendCommand(i, crawl_left_parameters);
			}
		}
		else if(reachingPart == "right_arm")
		{
			for(int i=0;i<nbParts;i++)
			{
				if(part_names[i] == "head")
				{
					continue;
				}
				if(connected_part[i]) sendCommand(i, crawl_right_parameters);
			}
		}
        Time::delay(2.0);
    }

	vector<vector<double> > reach_parameters;
	for(int i=0;i<nbParts;i++)
	{
		if(part_names[i] == "head")
		{
			continue;
		}
		if(connected_part[i])
		{
			ConstString currentPart = part_names[i];
			if(part_names[i] == ConstString(reachingPart.c_str())/* == currentPart*/)
			{
				vector<double> amplitude;
				vector<double> offset;
				for(int j=0; j<nbDOFs[i]; ++j)
				{
					amplitude.push_back(-1);
					offset.push_back(reachingCommand->get(j+1).asDouble());
				}
				reach_parameters.push_back(amplitude);
				reach_parameters.push_back(offset);
			}
			else
			{
				vector<double> amplitude;
				vector<double> offset;
				reach_parameters.push_back(init_parameters[2*i]);
				reach_parameters.push_back(init_parameters[2*i+1]);
			}
			sendCommand(i, reach_parameters);
		}
	}
}


//==========================================================//
//  HEAD CONTROL
//==========================================================//
void CrawlManagerModule::HeadControl(double pitchAngle, double yawAngle)
{
	vector<vector<double> > head_parameters;
	int headIndex;
	for(int i=0;i<nbParts;i++)
	{
		if(connected_part[i])
		{
			ConstString currentPart = part_names[i];
			if(part_names[i] == "head"/* == currentPart*/)
			{
				headIndex = i;
				vector<double> amplitude;
				vector<double> offset;
				amplitude.push_back(-1);
				offset.push_back(pitchAngle);

				amplitude.push_back(-1);
				offset.push_back(0);

				amplitude.push_back(-1);
				offset.push_back(yawAngle);

				for(int j=3; j<nbDOFs[i]; ++j)
				{
					amplitude.push_back(-1);
					offset.push_back(0.0);
				}
				head_parameters.push_back(amplitude);
				head_parameters.push_back(offset);
			}
			else
			{
				vector<double> amplitude;
				vector<double> offset;
				head_parameters.push_back(init_parameters[2*i]);
				head_parameters.push_back(init_parameters[2*i+1]);
			}
		}
	}
	sendCommand(headIndex, head_parameters);
}
