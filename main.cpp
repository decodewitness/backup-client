/***/
// BBCKUP27 ::      (Copyright) (C)(2020)
// -----            -----
     /***/
//  * , . ***::      DESCRIPTION:     *** (Tiny) Backup Program *** for Linux ( x86/amd64 ) ***
//   'o7o'
//     -     -----               -----
    /*0^0*/
// * ** *** ::      AUTHOR:          (Vera Lo) <!-- ( chatblanche767 <AT> gmail <DOT> com ) -->
//   /  \             -----               -----
    /***/
// * ** *** ::      DATE:            (Fri Oct 9 - 2020 A.D.) @ ( 8:55 P.M. )
//                  -----               -----
//
// === PROGRAM STARTS HERE ===


// header files
#include <iostream>
#include <fstream>

#include <cstring>
#include <cstdlib>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>


// namespace
using namespace std;

// global variables
const string VERSION = "v.0.1-1c (release candidate)";
const string PROGRAM_NAME = "BBCKUP27";
const string lo_PROGRAM_NAME = "bbckup27";
const string LICENSE_NUMBER = "YXXX-XYXX-XXYX-XXXD";
const string LOGFILE = "logfile__bbckup27.txt";

// main function
int main(int argc, char *argv[]) {

	// variables for catching help() function
	int j=2;
	bool redundancy=false;

	// switch DEBUG MODE for help() function !!!
	bool swD=false; // declaration here is used to debug the help function

	// function prototype help function
	void help(const string str, bool swD=true, int j=0);

	// catch help before registering too many things already.
	for (int i=1;i<=argc-1;i++) {
		if (argv[i][0] == '-' && strlen(argv[i])==6) {
			if (argv[i][1] == '-') j++;
			if (argv[i][2] == 'h') j++;
			if (argv[i][3] == 'e') j++;
			if (argv[i][4] == 'l') j++;
			if (argv[i][5] == 'p') j++;
			
			if (j==7) { // then yes '--help' was spelled.
				// passes j all the way to the help function.
				help(PROGRAM_NAME, swD, j);
				exit(0);	// make the program commit ritual suicide after help arrives.
			}	
		}
	}
	
	// files
	ofstream myfile2;
		
	void license(char n);
	int registerClient(bool swP, bool swR, bool swD=1);
	int ping(void);


//	void insertLicense();
//	void returnLicense();


	// variables
	int x=0, sw_count=0;    // receives return value from ping()
	string SRC, DEST, command;  // s

	// boolean switches
	/**/ swD=false;	// debug mode (already declared)
	bool swQ=false;	// quiet mode
	bool swA=false;	// show arguments
	bool swT=false;	// test run
	bool swL=false;	// logging
	bool swV=false;	// verbose mode

	bool swR=false;	// read registration
	bool swP=false;	// ping server
	bool swH=false;	// show usage
	bool swS=false;	// hide warnings and errors


	// boolean flags
	bool SRC_SET = false;
	bool DST_SET = false;

	// show help
	if (argc == 1 && swH==true) {
		help(argv[0], swD, j);
		cout << "CALLLLLLLLLED ! ! ! ! ! ! ! !" << endl;
	}

	// structures
	struct stat sb;

	// checks on directories && arguments
	bool CRC=false;     // check if SRC && DEST are correct
	bool redundant=false;  // used in check for arguments

	// check arguments and set switches and SRC && DEST
	for (int i=1; i<argc; i++) {
		if (argv[i][0] == '-') {
			sw_count++;
		}

		if (!CRC && argv[i][0] != '-' && !redundant) {
			SRC = argv[i];
			SRC_SET = true;
			redundant=true;
		} else if (!CRC && argv[i][0] != '-' && redundant) {
			DEST = argv[i];
			DST_SET = true;
			CRC=true;
		} else if (strlen(argv[i]) == 2 && argv[i][0] == '-') {
			switch (argv[i][1]) {
			case 'a':	// show arguments
				swA=true;
			break;

			case 'v':	// verbose
				swV=true;
			break;

			case 't':	// test run
				swT=true;
			break;

			case 'l':	// log
				swL=true;
				myfile2.open(LOGFILE.c_str());
				cout << "Opened: " << LOGFILE.c_str() << " for logging." << endl;
				myfile2 << "date: today.\n";
			break;

			case 'd':	// debug
				swD=true;
				if (redundancy == true) {
					help(PROGRAM_NAME, swD, j);
				}
			break;

			case 'p':	// ping server
				swP=true;
			break;

			case 'r':	// read registration
				swR=true;
			break;

			case 'h':	// show usage
				swH=true;
			break;

			case 's':	// hide error messages
				swS=true;
			break;

			case 'q':	// quiet modus
				swQ=true;
			break;

			default:
				if (!swS || !swQ) {
					cout << "- skipped invalid argument." << endl;
				}
			break;
			};
		} else if (CRC) {
			if (!swS || !swQ) {
				cout << "- skipped invalid argument." << endl;
			}
		}
	}


	// check arguments -&- first register client on ping
	if (swP) { x = registerClient(swP, swR); cout << "XXX::" << x; }


	if (argc == 1 || argc < 3 && strlen(argv[1]) > 1 && argv[1][0] != '-') {
		if ((!swS || !swQ) && swP != true) {
			cout << "- (ERROR)(#1022) - Too little arguments supplied. Use '$ " << lo_PROGRAM_NAME
				<< " -h' for HELP or use '$ " << lo_PROGRAM_NAME << " --help'" << endl
					<< "to see the built-in help() function." << endl << endl;
		}
		exit(1);
	} else if (argc == 2 && strlen(argv[1]) > 1 && argv[1][0] == '-' && argv[1][1] == 'h') {
		help(PROGRAM_NAME, swD, j);
	        exit(0);
	}
	if (argc > 6) {
		if (!swS || !swQ) {
			cout << "- (ERROR)(#1023) - Too many arguments supplied. Use '-h' for HELP." << endl << endl;
		}
		exit(1);
	}

	if (sw_count == argc-1) {
		if (!swS == false || swQ == false && swP != true && swR != true) {
			cout << "- (Warning) - Only using switches for the program. No SRC or DST were specified." << endl << endl;
		}
	} else {
		// show program name / splash intro
		if (!swQ) {
			cout << "*** " << PROGRAM_NAME << " " << VERSION << " ***" << endl << "   -----" << endl << endl;
		}
	}

	// show arguments
	if (swV || swA) {
		if (!swQ) {
			cout << "- ARGUMENTS: " << argc << endl << endl;
		}
		for (int i=0; i<argc; i++) {
			if (!swS || !swQ) {
				cout << argv[i] << " ";
			}
		}
		if (!swQ) {
			cout << endl;
		}
	}

	if (swR) {	// print license
		license(LICENSE_NUMBER.back());
	}

	if (CRC) {
		if (!swQ) {
			cout << "- CRC passed the failsafe device." << endl;	// SRC + DST are unique
		}
		CRC = false;
		redundant = false;
	}

	// check SRC
	if (SRC_SET) {
		if (!swQ) {
			cout << "- SRC set." << endl;
			cout << "- checking SRC." << endl;
		}

		if (stat(SRC.c_str(), &sb) == -1) {
			if (!swS || !swQ) {
				cout << "- (ERROR)(#1025) - stat() on directory." << endl;
			}
			exit(1);
		}

		switch (sb.st_mode & S_IFMT) {
			case S_IFDIR:
				if (!swQ) {
					cout << "- directory SRC found." << endl;
				}
				// set redundant value TRUE
				redundant = true;
			break;

			default:
				if (!swS || !swQ) {
					cout << "- (ERROR)(#1026) - SRC directory does not exist." << endl << endl;
				}
				exit(1);
			break;
		};
	} else {
		if ((!swS || !swQ) && swP != true) {
			cout << "- (ERROR)(#1024) - no SRC directory was specified." << endl << endl;
		}
		exit(1);
	}

	if (DST_SET) {
		// check DEST
		if (!swQ) {
			cout << "- DEST set." << endl;
			cout << "- checking DEST." << endl;
		}

		if (stat(DEST.c_str(), &sb) == -1) {
			if (!swS || !swQ) {
				cout << "- (ERROR)(#1027) - stat() on directory." << endl;
			}
			exit(1);
		}

		switch (sb.st_mode & S_IFMT) {
			case S_IFDIR:
				if (!swQ) {
					cout << "- directory DEST found." << endl;
				}
				// set CRC value TRUE
				CRC = true;
			break;

			default:
				if (!swS || !swQ) {
					cout << "- (ERROR)(#1028) - DEST directory does not exist." << endl << endl;
				}
				exit(1);
			break;
		};
	} else {
		if (!swS || !swQ) {
			cout << "(ERROR)(#1029) - No DST directory was specified or found." << endl << endl;
		}
	}

	// display result of checked SRC && DEST
	if (CRC && redundant) {
		if (!swQ) {
			cout << "- (CHECKED) SRC && DEST." << endl;
			cout << "\t -- using '" << SRC << "' for SOURCE." << endl;
			cout << "\t -- using '" << DEST << "' for DESTINATION." << endl;
		}
	}

	// === === === === ===

	// main program loop

	// main program
	// main program

	if (!swS || !swQ) {
		cout << endl << "- generating system command to use for backing up." << endl;
	}

	// set command
	command = "7z a -y " + DEST + "/file.7z " + SRC;

	// log DEST + SRC
	if (swL) {
		myfile2 << command;
		myfile2 << "\nSRC: ";
		myfile2 << SRC.c_str();
		myfile2 << "\nDEST: ";
		myfile2 << DEST.c_str();
		myfile2 << "\n\n";
	}

	// run command
	if (!swT) {
		if (!swS || !swQ) {
			cout << endl << "- running command." << endl;
			cout << endl << "- COMMAND:" << endl << "-----" << endl << "\t" << command << endl;
		}

		// actually run command
		system(command.c_str());
	} else { // run test run
		if (!swS || !swQ) {
			cout << endl << "- running command." << endl;
			cout << endl << "- COMMAND:" << endl << "-----" << endl << "\t" << command << endl;

			// display test run message
			cout << "-------------------------------------------------" << endl;
			cout << endl << "(TEST RUN) Not Actually Backing Up !!! (TEST RUN)" << endl << endl;
		}
	}

	// === === === === ===

	// clean up
	if (swL) {
		myfile2.close();
	}

	swT = false;
	swL = false;
	swV = false;
	swD = false;
	swP = false;
	swA = false;
	swL = false;

	CRC = false;
	SRC = "\0";
	DEST = "\0";

	command = "\0";

	// show final message
	if (!swQ) {
		cout << endl << "----" << endl;
		cout << PROGRAM_NAME << " finished (%100)." << endl << endl;
	}

return 0;
}

// help function
void help(const string str, bool swD=1, int j=0) {

	cout << "-----" << endl;
	cout << PROGRAM_NAME <<" Usage:" << endl;
	cout << "Version " << VERSION << endl;
	cout << "-----" << endl << endl;
	cout << "\t" << PROGRAM_NAME << " -[option 1] -[option 2] <SOURCE> <DESTINATION>" << endl;
	cout << endl;
	cout << "\t(Specify <SOURCE> first)" << endl << endl;
	cout << "\tSwitches/Options:" << endl << "-----" << endl;
	cout << "\t-a = SHOW ARGUMENTS" << endl;
	cout << "\t-h or --help = SHOW USAGE/HELP FUNCTION" << endl;
	cout << "\t-v = VERBOSE" << endl;
	cout << "\t-l = ENABLE LOGGING" << endl;
	cout << "\t-t = SIMULATE TEST RUN (NOT ACTUALLY BACK UP)" << endl;
	cout << "\t-d = DEBUG MODE" << endl;
	cout << "\t-p = REGISTER CLIENT" << endl;
	cout << "\t-r = TYPE LICENSE" << endl;
	cout << endl << "-----" << endl << endl;
	cout << "This Linux program depends on the \"p7zip-full\" package." << endl << endl;
	cout << "Copyright (C)(2020) Vera Lo - chatblanche767 <AT> gmail <dot> com" << endl
		<< "- All rights are reserved (C)(2021)." << endl << endl << PROGRAM_NAME << endl;
	cout << "(Available for Download at): https://decodewitness.github.io/backup-client/ ." << endl << endl;

	if (swD) {
		cout << "DEBUG MSG***::help detector (j should be '7')" << "\tJ=>>>" << j << endl;
	}
}


int ping(void) {
	// ping home to the server
	cout << "-- ping" << endl << endl;
	system("ping localhost -c 1");
	cout << endl << "\t-- pong" << endl << endl;

return 1;
}


int registerClient(bool swP, bool swR, bool swD=true) {

	int ping(void);
	int x;

	char c;

	// check existing file
	std::ifstream ifs;


	if (swP) {
		cout << "Registering your client from our local server." << endl << endl;
		x = ping();

		cout << "-- event(" << x << ")" << endl;

		if (x == 1) {
			cout << "Client successfully registered." << endl;

			if (swR) {
				ifs.open("test.txt", std::ifstream::in);

				c = ifs.get();

				while (ifs.good()) {
					std::cout << c;
					c = ifs.get();
					
					if (swD) {
						cout << "X" << c << endl;
					}
				}

				ifs.close();
			}
		}
	}

	return 0;
}

void license(char n='q') {
	cout << "ENTERS FUNCTION" << endl << endl;
	cout << "License Number: " << LICENSE_NUMBER << " Type: ";

	char c = LICENSE_NUMBER.back();	// looks at last char of LICENSE_NUMBER

	switch ((n=='q')?c:n) {
		case 'C':
			cout << "(Commercial)";	// C
		break;

		case 'E':
			cout << "(Enterprise)";	// E
		break;

		case 'P':
			cout << "(Private)";		// P
		break;

		case 'S':
			cout << "(Shareware)";	// S
		break;

		case 'T':
			cout << "(Trial)";		// T
		break;

		case 'F':
			cout << "(Freeware)";		// F
		break;

		case 'D':
			cout << "(DEVEL)";		// D
		break;

		case 'Z':		// prohibited client
		default:
			cout << endl << "There was an error with your license and registration number. Not registered." << endl << endl;
		break;
	};

	cout << endl << endl;

	exit(0);
}

/*
void returnLicense(char n='q') {	// diplays license and category in the client

	cout << "License Number: " << LICENSE_NUMBER << " Type: ";
	char c = LICENSE_NUMBER.back();	// looks at last char of LICENSE_NUMBER

	switch ((n=='q')?c:n) {
		case 'C':
			cout << "(Commercial)";	// C
		break;

		case 'E':
			cout << "(Enterprise)";	// E
		break;

		case 'P':
			cout << "(Private)";		// P
		break;

		case 'S':
			cout << "(Shareware)";	// S
		break;

		case 'T':
			cout << "(Trial)";		// T
		break;

		case 'F':
			cout << "(Freeware)";		// F
		break;

		case 'D':
			cout << "(DEVEL)";		// D
		break;

		case 'Z':		// prohibited client
		default:
			cout << endl << "There was an error with your license and registration number. Not registered." << endl << endl;
		break;
	};

	cout << endl << endl;

	exit(0);
}


void insertLicense() {

	// function prototype
	void returnLicense(char n);

	cout << "ENTERS FUNCTION" << endl;

	// function prototype
	int typeLicense(char c);

	// variables
	int n;		// holds license
	char c;	// holds last char of LICENSE_NUMBER

	cout << LICENSE_NUMBER << " Type: ";

	c = LICENSE_NUMBER.back();	// looks at last char of LICENSE_NUMBER
	n = typeLicense(c);	// fetches type of regustration

	cout << LICENSE_NUMBER << " ";

	returnLicense(c);

	// switch statement that displays the the type of license
	/*switch (n) {
		case 1:
			cout << "(Commercial)" << endl << endl;	// C
		break;

		case 2:
			cout << "(Enterprise)" << endl << endl;	// E
		break;

		case 3:
			cout << "(Private)" << endl << endl;		// P
		break;

		case 4:
			cout << "(Shareware)" << endl << endl;	// S
		break;

		case 5:
			cout << "(Trial)" << endl << endl;		// T
		break;

		case 6:
			cout << "(Freeware)" << endl << endl;		// F
		break;

		case 101:
			cout << "(DEVEL)" << endl << endl;		// D
		break;

		case '0':
		default:
			cout << "There was an error with your license and registration number. Not registered." << endl << endl;
		break;
	};
}
*/
/*
int typeLicense(char c='z') {	// decides what type of license is supplied (for now by looking at the last char of license)
	// open registration file

	if (c == 'z') {	// default case
		return 0;
	}

	if (c == 'C') {	// commercial license
		return 1;
	}

	if (c == 'E') {	// enterprise license
		return 2;
	}

	if (c == 'P') {	// private license
		return 3;
	}

	if (c == 'S') {	// shareware license
		return 4;
	}

	if (c == 'T') {	// trial version license
		return 5;
	}

	if (c == 'F') {	// freeware license
		return 6;
	}

	if (c == 'D') {	// developer license
		return 101;
	}

return 0;
}*/



// eof
