#include "NS_Task_1_Sandbox.h"
#include "list"
/*
**
Team Id: <1868>
* Author List: <Hardik,Shayan,Jasneet,Vinay>
* Filename: <NS_Task_1_Sandbox>
* Theme: <Nutty Squirrell>
* Functions: <forward_wls,backward_wls,left_wls,right_wls,read_sensors,motor_drive,identify_node>
* Global Variables: <line , Case , node , flag,prev,current>
**/


// CPP code for printing shortest path between
// two vertices of unweighted graph
const int v = 24;// no. of vertices
int prev = 0;
int current = 0;

using namespace std;



int line = 50; 	 // Contains the threshold value to distinguish between black and white
int Case = 0;	// Stores the case number as defined in function "read_sensors"
int node = 0;	// Stores the count of node
int flag = 0;	// Used to break the loop after the track is completed
int dir_robot = 0;
int alblk = 0;

/*
*
* Function Name: forward_wls
* Input: integer
* Output: void
* Logic: crosses that number of nodes 
* Example Call: forward_wls(2); //Goes forward for that number of nodes
*
*/
void forward_wls(unsigned char node)
{
	forward();
	_delay_ms(50);
	while (alblk != node)
	{
		read_sensors();
		motor_drive();
		if ((ADC_Conversion(1) > line) && (ADC_Conversion(2) > line) && (ADC_Conversion(3) > line))    //// B B B
		{
			while (((ADC_Conversion(1) > line) && (ADC_Conversion(2) > line) && (ADC_Conversion(3) > line)));
			_delay_ms(10);
			alblk++;

		}

	}
	alblk = 0;
	forward();
	_delay_ms(50);

}
//forward movement with delay given in the function 

/*
*
* Function Name: backward_wls
* Input: integer
* Output: void
* Logic: crosses that number of nodes
* Example Call: backward_wls(2); //Goes backward for that number of nodes
*
*/
void backward_wls(unsigned char node)
{	
	back();
	_delay_ms(50);
	while (alblk != node)
	{
		read_sensors();
		motor_drive();
		if ((ADC_Conversion(1) > line) && (ADC_Conversion(2) > line) && (ADC_Conversion(3) > line))    //// B B B
		{
			while (((ADC_Conversion(1) > line) && (ADC_Conversion(2) > line) && (ADC_Conversion(3) > line)));
			_delay_ms(10);
			alblk++;
			stop();

		}

	}
	alblk = 0;
	back();
	_delay_ms(50);
}

/*
*
* Function Name:left_turn_wls
* Input: no
* Output: void
* Logic: left till there comes a black line in middle of bot
* Example Call :left_turn_wls
*
*/
void left_turn_wls(void)
{
	left();
	_delay_ms(200);
	while ((ADC_Conversion(1) < line))  //bot will rotate left till left most sensor is on white
	{
		left();
	}
	_delay_ms(80);

}
//left until middle is black or left is on white

/*
*
* Function Name:right_turn_wls(
* Input: NO
* Output: void
* Logic:right till there comes a black line in middle of bot
* Example Call :right_turn_wls(
*
*/
void right_turn_wls(void)
{
	right();
	_delay_ms(200);
	while ((ADC_Conversion(3) < line))   //bot will rotate right till right most sensor is on white
	{
		right();

	}
	_delay_ms(80);

}
//right until middle is black or right is on white

/*
*
* Function Name:read_sensors
* Input: vector<int> adj[], int src, int dest
* Output: void
* Logic:get the reading of the sensors
* Example Call :read_sensors(void)
*
*/
void read_sensors(void)
{
	if ((ADC_Conversion(1) < line) && (ADC_Conversion(2) > line) && (ADC_Conversion(3) > line))    //// W B B
	{
		Case = 2;    //right

	}
	else if ((ADC_Conversion(1) < line) && (ADC_Conversion(2) < line) && (ADC_Conversion(3) > line))     ////   W W B
	{
		Case = 1; //right

	}
	else if ((ADC_Conversion(1) < line) && (ADC_Conversion(2) > line) && (ADC_Conversion(3) < line))  ////line in between
	{
		Case = 0; // forward
	}
	else if ((ADC_Conversion(1) > line) && (ADC_Conversion(2) < line) && (ADC_Conversion(3) < line))  ///// B W W
	{
		Case = -1;  //left
	}
	else if ((ADC_Conversion(1) > line) && (ADC_Conversion(2) > line) && (ADC_Conversion(3) < line))    //// B B W
	{
		Case = -2;  //left

	}
	else if ((ADC_Conversion(1) < line) && (ADC_Conversion(2) < line) && (ADC_Conversion(3) < line))  ////all white
	{
		if (Case > 0)
		{
			Case = 4;
		}
		else
		{
			Case = -4;
		}
	}
}
//cases for the position of ir is covered in this part

void motor_drive(void)
{
	if (Case == 0)   //forward
	{
		velocity(255, 255);
		forward();

	}
	else if (Case == 1)   //soft right 
	{
		soft_right();
	}
	else if (Case == 2) //more softer right
	{
		forward();
		velocity(250, 180);

	}
	else if (Case == -1)   //soft left 
	{
		soft_left();
	}
	else if (Case == -2)   //more softer left
	{

		forward();
		velocity(180, 250);


	}
	else if (Case == -4)  //soft left
	{
		soft_left();

	}
	else if (Case == 4)  //soft right
	{
		soft_right();

	}

	else
	{
		stop();
	}
}

//Graph initialisation for the working of the bot
//]function to form edge between two vertices
// source and dest


/*
*
* Function Name:identify_node
* Input: node 
* Output: void
* Logic:to find which node is this
* Example Call :identify_node()
*
*/
void identify_node(void)
{
	//printf(" mein a gya \n");

	//while ((ADC_Conversion(1) > line) && (ADC_Conversion(2) > line) && (ADC_Conversion(3) > line))
	//{
	//	forward();
	//}
	//_delay_ms(20);
	stop();
	printf(" node %d \n", node);
	if (node == 1)
	{

		right_turn_wls();
	}
	if (node == 2)
	{

		forward_wls(4);
		left_turn_wls();

	}
	if (node == 3)
	{

		left_turn_wls();
	}
	if (node == 4)
	{

		left_turn_wls();
	}
	if (node == 5)
	{

		right_turn_wls();
	}

	if (node == 6)
	{

		forward_wls(2);
	}
	if (node == 7)
	{

		forward_wls(2);
	}
	if (node == 8)
	{
		//forward_wls(2);
		right_turn_wls();
	}
	if (node == 9)
	{

		left_turn_wls();
	}
	if (node == 10)
	{

		left_turn_wls();
	}
	if (node == 11)
	{
		//left_turn_wls();
		left();
		_delay_ms(200);
		forward_wls(4);
	}
	if (node == 12)
	{

		right_turn_wls();
	}
	if (node == 13)
	{
		flag = 1;
		stop();
		scanf(" ");
	}
}


/*
*
* Function Name:add_edge
* Input: vector<int> adj[], int src, int dest
* Output: void
* Logic: add the node with source and desstination
* Example Call :add_edge(vector<int> adj[], int src, int dest)
*
print short distance returns the array with the shortest path 
*/
void add_edge(vector<int> adj[], int src, int dest)
{
	adj[src].push_back(dest);
	adj[dest].push_back(src);
}

bool BFS(vector<int> adj[], int src, int dest, int x, int pred[], int dist[])
{
	// a queue to maintain queue of vertices whose
	// adjacency list is to be scanned as per normal
	// DFS algorithm
	list<int> queue;

	// boolean array visited[] which stores the
	// information whether ith vertex is reached
	// at least once in the Breadth first search
	bool visited[v];

	// initially all vertices are unvisited
	// so v[i] for all i is false
	// and as no path is yet constructed
	// dist[i] for all i set to infinity
	for (int i = 0; i < v; i++) {
		visited[i] = false;
		dist[i] = INT_MAX;
		pred[i] = -1;
	}

	// now source is first to be visited and
	// distance from source to itself should be 0
	visited[src] = true;
	dist[src] = 0;
	queue.push_back(src);

	// standard BFS algorithm
	while (!queue.empty()) {
		int u = queue.front();
		queue.pop_front();
		for (int i = 0; i < adj[u].size(); i++) {
			if (visited[adj[u][i]] == false) {
				visited[adj[u][i]] = true;
				dist[adj[u][i]] = dist[u] + 1;
				pred[adj[u][i]] = u;
				queue.push_back(adj[u][i]);

				// We stop BFS when we find
				// destination.
				if (adj[u][i] == dest)
					return true;
			}
		}
	}

	return false;
}

// utility function to print the shortest distance
// between source vertex and destination vertex
int *printShortestDistance(vector<int> adj[], int s, int dest, int x)
{

	// predecessor[i] array stores predecessor of
	// i and distance array stores distance of i
	// from s
	int pred[v], dist[v];
	int *pathreturn = new int[20];

	if (BFS(adj, s, dest, v, pred, dist) == false)
	{
		cout << "Given source and destination"
			<< " are not connected";
		return 0;
	}

	// vector path stores the shortest path
	vector<int> path;
	int crawl = dest;
	path.push_back(crawl);
	while (pred[crawl] != -1) {
		path.push_back(pred[crawl]);
		crawl = pred[crawl];
	}

	// distance from source is in distance array
	cout << "\nShortest path length is : "
		<< dist[dest];

	// printing path from source to destination
	cout << "\nPath is:: ";
	int k = 0;
	for (int i = path.size() - 1; i >= 0; i--)
	{
		cout << path[i] << " ";
		pathreturn[k] = int(path[i]);
		k++;
	}
	pathreturn[k] = 99;
	return pathreturn;
}

//during the start of the program the variables will be initialised zero as the obstacles are found in the path 
//that edges will be not added further 





// array of vectors is used to store the graph
// in the form of an adjacency list
// Creating graph given in the above diagram.
// add_edge function takes adjacency list, source
// and destination vertex as argument and forms
// an edge between them.





//to add the nodes in the graph 
vector<int> adj[v];

int a15 = 0, a14 = 0, a18 = 0, a21 = 0;


/*
*
* Function Name: Create graph
* Input: Void
* Output: void
* Logic: to initialise the graph
* Example Call : creategraph
*
print short distance returns the array with the shortest path
*/
void creategraph()
{ //variables initialised in the start of program int a15 = 0, a14 = 0, a18 = 0, a21 = 0;

	{
		add_edge(adj, 1, 2);
		add_edge(adj, 2, 3);
		add_edge(adj, 2, 15);
		add_edge(adj, 2, 14);
		add_edge(adj, 2, 1);
		add_edge(adj, 3, 2);
		add_edge(adj, 3, 4);
		add_edge(adj, 3, 7);
		add_edge(adj, 4, 3);
		add_edge(adj, 4, 5);
		add_edge(adj, 5, 4);
		add_edge(adj, 5, 12);
		add_edge(adj, 5, 6);
		add_edge(adj, 6, 5);
		add_edge(adj, 6, 13);
		add_edge(adj, 13, 6);
		add_edge(adj, 13, 12);
		add_edge(adj, 13, 21);
		add_edge(adj, 12, 5);
		add_edge(adj, 12, 13);
		add_edge(adj, 12, 15);
		add_edge(adj, 15, 2);
		add_edge(adj, 15, 12);
		add_edge(adj, 19, 20);
		add_edge(adj, 20, 19);
		add_edge(adj, 20, 21);
		add_edge(adj, 21, 13);
		add_edge(adj, 21, 20);
		add_edge(adj, 7, 3);
		add_edge(adj, 7, 8);
		add_edge(adj, 8, 7);
		add_edge(adj, 8, 11);
		add_edge(adj, 8, 9);
		add_edge(adj, 9, 10);
		add_edge(adj, 9, 8);
		add_edge(adj, 11, 8);
		add_edge(adj, 11, 10);
		add_edge(adj, 10, 9);
		add_edge(adj, 10, 11);
		add_edge(adj, 10, 16);
		add_edge(adj, 14, 2);
		add_edge(adj, 14, 18);
		add_edge(adj, 18, 14);
		add_edge(adj, 18, 17);
		add_edge(adj, 17, 18);
		add_edge(adj, 17, 16);
		add_edge(adj, 16, 17);
		add_edge(adj, 16, 10);
		add_edge(adj, 16, 22);
		add_edge(adj, 22, 16);
		if (a15 == 0)
		{
			add_edge(adj, 15, 19);
			add_edge(adj, 19, 15);
		}
		if (a14 == 0)
		{
			add_edge(adj, 11, 14);
			add_edge(adj, 14, 11);
		}
		if (a18 == 0)
		{
			add_edge(adj, 19, 18);
			add_edge(adj, 18, 19);
		}
		if (a21 == 0)
		{
			add_edge(adj, 21, 23);
			add_edge(adj, 23, 21);
		}


	}
}

/*
*
* Function Name: initialise the graph 
* Input: Void
* Output: void
* Logic: to initialise the graph with the array used for direction finding
* Example Call : creategraph
*
print short distance returns the array with the shortest path
*/
int *graphInit(int source, int dest)
{
	creategraph();

	//source = 1, dest = 6;
	int *series = printShortestDistance(adj, source, dest, v);

	printf("Things are returned back now\n\n");

	return series;
}

int prev_x = 0, prev_y = 0;
int current_x = 0, current_y = 0;


int get_dir(int prev, int current)
{
	

	int arr[10][10] = { {9,0,8,7,3,4,5,0,6},
						{10,0,11,0,0,0,12,0,13},
						{0,0,14,0,2,0,15,0,0},
						{16,17,18,0,1,0,19,20,21},
						{22,0,0,0,0,0,0,0,23} };
	//the array to provide direction to the bot 

	//Declaring them as global variables

	//int prev_x = 0, prev_y = 0;
	//int current_x = 0, current_y = 0;

	int cflag = 0, nflag = 0, pflag = 0;

	//finding the index of nodes only
	for (int p = 0; p < 5; p++)
	{

		for (int m = 0; m < 9; m++)
		{
			if (arr[p][m] == current)
			{
				current_y = p;
				current_x = m;
				cflag = 1;
				//cout << "found " << current << " at " << p << " " << m << "\n";

			}

			if (arr[p][m] == prev)
			{
				prev_y = p;
				prev_x = m;
				pflag = 1;
				//cout << "found " << current << " at " << p << " " << m << "\n";

			}
			if ((cflag == 1) && (pflag == 1))
			{
				break;
			}
		}

	}
	//direction finder 0-north 1-south 2-east 3-west

	if (prev_x == current_x)
	{
		if ((prev_y - current_y) > 0)
		{
			cout << "north\n";
			dir_robot = 0;
			cout << "prev_y: " << prev_y << " current_y: " << current_y << endl;
		}
		else if ((prev_y - current_y) < 0)
		{
			cout << "south\n";
			dir_robot = 1;
			cout << "prev_y: " << prev_y << " current_y: " << current_y << endl;
		}
		else
		{
			cout << "last dir\n";
			//dir_robot = 0;
			cout << "prev_y: " << prev_y << " current_y: " << current_y << endl;
		}

	}

	if (prev_y == current_y)
	{
		if ((prev_x - current_x) > 0)
		{
			cout << "west\n";
			dir_robot = 3;
			cout << "prev_x: " << prev_x << " current_x: " << current_x << endl;
		}
		else if ((prev_x - current_x) < 0)
		{
			cout << "east\n";
			dir_robot = 2;
			cout << "prev_x: " << prev_x << " current_x: " << current_x << endl;
		}
		else
		{
			cout << "last dir\n";
			//dir_robot = 0;
			cout << "prev_x: " << prev_x << " current_x: " << current_x << endl;
		}

	}

	if (current == 19 && prev == 18)
	{
		dir_robot = 0;
	}
	if (current == 18 && prev == 19)
	{
		dir_robot = 0;
	}



	return 0;

}

int move_dir(int current, int next)
{
	cout << "current: " << current << "  next: " << next << endl;
	if (dir_robot == 0)//north
	{
		if (current == 1)
		{
			if (next == 2)
			{
				forward_wls(1);
			}
		}
		if (current == 2)
		{
			if (next == 3)
			{
				forward_wls(1);
			}
			if (next == 14)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 15)
			{
				right_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 3)
		{
			if (next == 4)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 7)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 4)
		{
			if (next == 5)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 3)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 5)
		{
			if (next == 6)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 4)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 12)
			{
				left_turn_wls();
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 6)
		{
			if (next == 13)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 5)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 7)
		{
			if (next == 3)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 8)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 8)
		{
			if (next == 7)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 9)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 11)
			{
				left_turn_wls();
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 9)
		{
			if (next == 8)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 10)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 10)
		{
			if (next == 9)
			{
				forward_wls(1);
			}
			if (next == 11)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 16)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 11)
		{
			if (next == 8)
			{
				forward_wls(1);
			}
			if (next == 10)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 14)
			{
				right_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 12)
		{
			if (next == 13)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 5)
			{
				forward_wls(1);
			}
			if (next == 15)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 13)
		{
			if (next == 21)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 12)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 6)
			{
				forward_wls(1);
			}
		}
		if (current == 14)
		{
			if (next == 2)
			{
				forward_wls(1);
			}
			if (next == 11)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 15)
		{
			if (next == 12)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 2)
			{
				forward_wls(1);
				soft_left();
				_delay_ms(50);
			}
		}
		if (current == 16)
		{
			if (next == 17)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 22)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 10)
			{
				forward_wls(1);
			}
		}
		if (current == 17)
		{
			if (next == 18)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 16)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 18)
		{
			if (next == 14)
			{
				forward_wls(1);
			}
			if (next == 17)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 19)
			{
				right_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 19)
		{
			if (next == 20)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 18)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 15)
			{
				forward_wls(1);
			}
		}
		if (current == 20)
		{
			if (next == 21)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 19)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 21)
		{
			if (next == 23)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 20)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 13)
			{
				forward_wls(1);
			}
		}
		if (current == 22)
		{
			if (next == 16)
			{
				forward_wls(1);
			}
		}
		if (current == 23)
		{
			if (next == 21)
			{
				forward_wls(1);
			}
		}
	}

	if (dir_robot == 1) //south
	{

		if (current == 2)
		{
			if (next == 1)
			{
				forward_wls(1);
			}
			if (next == 15)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 14)
			{
				right_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 3)
		{
			if (next == 7)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 3)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 4)
		{
			if (next == 3)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 5)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 5)
		{
			if (next == 4)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 6)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 12)
			{
				forward_wls(1);
			}
		}
		if (current == 6)
		{
			if (next == 13)
			{
				forward_wls(1);
			}
			if (next == 5)
			{
				right_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 7)
		{
			if (next == 8)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 3)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 8)
		{
			if (next == 9)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 7)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 11)
			{
				forward_wls(1);
			}
		}
		if (current == 9)
		{
			if (next == 10)
			{
				forward_wls(1);
			}
			if (next == 8)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 10)
		{
			if (next == 16)
			{
				forward_wls(1);
			}
			if (next == 9)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 11)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 11)
		{
			if (next == 14)
			{
				forward_wls(1);
			}
			if (next == 8)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 10)
			{
				right_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 12)
		{
			if (next == 5)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 15)
			{
				forward_wls(1);
			}
			if (next == 13)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 13)
		{
			if (next == 12)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 6)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 21)
			{
				forward_wls(1);
			}
		}
		if (current == 14)
		{
			if (next == 18)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 2)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 11)
			{

				forward_wls(1);
			}
		}
		if (current == 15)
		{
			if (next == 2)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 19)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 12)
			{

				forward_wls(1);
			}
		}
		if (current == 16)
		{
			if (next == 10)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 17)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 22)
			{
				forward_wls(1);
			}
		}
		if (current == 17)
		{
			if (next == 16)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 18)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 18)
		{
			if (next == 19)
			{
				forward_wls(1);
			}
			if (next == 14)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 17)
			{
				right_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 19)
		{
			if (next == 15)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 20)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 18)
			{
				forward_wls(1);
			}
		}
		if (current == 20)
		{
			if (next == 19)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 21)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 21)
		{
			if (next == 20)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 13)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 23)
			{
				forward_wls(1);
			}
		}
		if (current == 22)
		{
			if (next == 16)
			{
				right_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 23)
		{
			if (next == 21)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
	}

	if (dir_robot == 2)//east
	{

		if (current == 2)
		{
			if (next == 15)
			{
				forward_wls(1);
			}
			if (next == 3)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 1)
			{
				right_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 3)
		{
			if (next == 4)
			{
				forward_wls(1);
			}
			if (next == 7)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 2)
			{
				right_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 4)
		{
			if (next == 5)
			{
				forward_wls(1);
			}
		}
		if (current == 5)
		{
			if (next == 6)
			{
				forward_wls(1);
			}
			if (next == 12)
			{
				right_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 6)
		{
			if (next == 13)
			{
				right_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 7)
		{
			if (next == 3)
			{
				forward_wls(1);
			}

		}
		if (current == 8)
		{
			if (next == 11)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 7)
			{
				forward_wls(1);
			}
		}
		if (current == 9)
		{
			if (next == 10)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 8)
			{
				forward_wls(1);
			}
		}
		if (current == 10)
		{
			if (next == 11)
			{
				forward_wls(1);
			}
			if (next == 16)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 9)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 11)
		{
			if (next == 8)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 14)
			{
				right_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 12)
		{
			if (next == 13)
			{
				forward_wls(1);
			}
		}
		if (current == 13)
		{
			if (next == 21)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 6)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 14)
		{
			if (next == 2)
			{
				forward_wls(1);
			}

		}
		if (current == 15)
		{
			if (next == 12)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 19)
			{
				forward_wls(1);
				soft_right();
				_delay_ms(50);
			}
		}
		if (current == 16)
		{
			if (next == 22)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 10)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 17)
			{
				forward_wls(1);
			}
		}
		if (current == 17)
		{
			if (next == 18)
			{
				forward_wls(1);
			}

		}
		if (current == 18)
		{

			if (next == 14)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 19)
			{
				right_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 19)
		{
			if (next == 18)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 15)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 20)
			{
				forward_wls(1);
			}
		}
		if (current == 20)
		{
			if (next == 21)
			{
				forward_wls(1);
			}
		}
		if (current == 21)
		{
			if (next == 23)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 13)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 22)
		{
			if (next == 16)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 23)
		{
			if (next == 21)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
	}

	if (dir_robot == 3)//west
	{

		if (current == 2)
		{
			if (next == 14)
			{
				forward_wls(1);
			}
			if (next == 1)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 3)
			{
				right_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 3)
		{
			if (next == 7)
			{
				forward_wls(1);
			}
			if (next == 2)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 4)
			{
				right_turn_wls();
				forward_wls(1);
			}
		}

		if (current == 4)
		{
			if (next == 3)
			{
				forward_wls(1);
			}
		}
		if (current == 5)
		{
			if (next == 4)
			{
				forward_wls(1);
			}
			if (next == 12)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 6)
		{
			if (next == 13)
			{
				left_turn_wls();
				forward_wls(1);
			}

			if (next == 5)
			{
				forward_wls(1);
			}
		}
		if (current == 7)
		{
			if (next == 8)
			{
				forward_wls(1);
			}

		}
		if (current == 8)
		{
			if (next == 11)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 9)
			{
				forward_wls(1);
			}
		}
		if (current == 9)
		{
			if (next == 10)
			{
				left_turn_wls();
				forward_wls(1);
			}

		}
		if (current == 10)
		{

			if (next == 9)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 16)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 11)
		{
			if (next == 10)
			{

				forward_wls(1);
			}
		}
		if (current == 12)
		{
			if (next == 5)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 15)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 13)
		{
			if (next == 6)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 21)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 12)
			{
				forward_wls(1);
			}
		}
		if (current == 14)
		{
			if (next == 11)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 18)
			{
				forward_wls(1);
			}

		}
		if (current == 15)
		{

			if (next == 2)
			{
				forward_wls(1);
			}
		}
		if (current == 16)
		{
			if (next == 10)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 22)
			{
				left_turn_wls();
				forward_wls(1);
			}

		}
		if (current == 17)
		{
			if (next == 16)
			{
				forward_wls(1);
			}

		}
		if (current == 18)
		{

			if (next == 19)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 14)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 17)
			{
				forward_wls(1);
			}
		}
		if (current == 19)
		{
			if (next == 15)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 18)
			{
				left_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 20)
		{
			if (next == 19)
			{
				forward_wls(1);
			}
		}
		if (current == 21)
		{
			if (next == 13)
			{
				right_turn_wls();
				forward_wls(1);
			}
			if (next == 23)
			{
				left_turn_wls();
				forward_wls(1);
			}
			if (next == 20)
			{
				forward_wls(1);
			}
		}
		if (current == 22)
		{
			if (next == 16)
			{
				right_turn_wls();
				forward_wls(1);
			}
		}
		if (current == 23)
		{
			if (next == 21)
			{
				right_turn_wls();
				forward_wls(1);
			}
		}
	}

	return 0;
}

int pickup_points[6] = { 4,5,6,7,8,9 };
int pick_point = 0;
int drop_point_red = 0;
int drop_points_red[2] = { 22,17 };
int drop_points_green[2] = { 20,19 };
int drop_point_green = 0;
int color;
int test;
int flagdg = 0, flagdr = 0;

//int to, from;
int updated_point = 1;
int object = 0;

/*
*
* Function Name:Traverse
* Input: To and From 
* Output: void
* Logic: to traverse through the graph
* Example Call : traverse(int from, int to)
*
print short distance returns the array with the shortest path
*/
void traverse(int from, int to)
{
	int *path = graphInit(from, to);
	int k = 1;
	while (path[k] != 99)
	{
		if ((k - 2) < 0)
		{
			get_dir(path[k - 1], path[k - 1]);//previous,current
			move_dir(path[k - 1], path[k]);//current,next
		}
		else
		{
			get_dir(path[k - 2], path[k - 1]);//previous,current
			move_dir(path[k - 1], path[k]);//previous,current
		}
		printf("\n");
		cout << "step:" << k << endl;
		k++;

	}
}


int color_detect(void)
{
	unsigned int blue_color_count, green_color_count, red_color_count, clear_count, distance_object = ADC_Conversion(FRONT_IR_ADC_CHANNEL);


	filter_blue();
	blue_color_count = color_sensor_pulse_count;
	filter_green();
	green_color_count = color_sensor_pulse_count;
	filter_red();
	red_color_count = color_sensor_pulse_count;
	filter_clear();
	clear_count = color_sensor_pulse_count;
	printf("\nblue = %d ,  green = %d ,  red = %d ,  clear = %d ,  distance = %d\n", blue_color_count, green_color_count, red_color_count, clear_count, distance_object);

	int a = ADC_Conversion(4);
	int x = prev_x;
	if ((10 < a) && (a < 60))
	{
		if ((red_color_count < 3500) && (green_color_count > 3500))
		{
			printf("\nGreen nut \n");
			pick();
			return 1;
		}
		else if ((red_color_count > 3500) && (green_color_count < 3500))
		{
			printf("\nRed nut \n");
			pick();
			return 2;
		}
		else if ((red_color_count < 3500) && (green_color_count < 3500))
		{
			printf("\nObstacle Founded \n");
			stop();
			backward_wls(1);
	
			//To not consider the edges of the graph further as they are blocked
			if (current == 15)
				a15 = 1;
			else if (current == 14)
				a14 = 1;
			else if (current == 18)
				a18 = 1;
			else if (current == 21)
				a21 = 1;
			
			traverse(current,x);

		}

	}
	else
		return 3;

	//_delay_ms(1000);
}

void Square(void)
{
	forward();
	_delay_ms(3000);
	soft_left();
	_delay_ms(400);
	forward();
	_delay_ms(1000);
	soft_left();
	_delay_ms(400);
	forward();
	_delay_ms(1000);
	soft_left();
	_delay_ms(400);
	forward();
	_delay_ms(1000);
	soft_left();
	_delay_ms(400);
}

void Task_1_1(void)
{

	forward_wls(5); //Moves forward for 500 milliseconds to avoid first all black condition
	while (1)  // infinite loop (untill breaked)
	{
		read_sensors();   // call read_sensors function
		motor_drive();	  // call motor_drive function
		
		if (flag == 1)
		{
			break;
		}

		//////////////////////////////////////////
	}
}


void Task_1_2(void)
{
	creategraph();

	stop();
	cin >> test;
	forward_wls(1);

	while (object < 4)
	{

		traverse(updated_point, pickup_points[pick_point]);

		if (flag == 0) {
			left_turn_wls();
			flag++;
		}
		else if (flag == 1) {
			left_turn_wls();
			flag++;
		}
		else if (flag == 2) {
			forward();
			_delay_ms(50);
			flag++;
		}
		else if (flag == 3) {
			left_turn_wls();
			flag++;
		}
		else if (flag == 4) {
			right_turn_wls();
			flag++;
		}
		else if (flag == 5) {
			//left_turn_wls();
			flag++;
		}


		cout << "aaaa " << dir_robot;

		stop();
		_delay_ms(100);
		color = color_detect();
		cout << "utha liya ";

		if (color == 1)
		{
			cout << "green";
			//int *path = graphInit( pickup_points[pick_point],drop_points_green[drop_point_green]);
			dir_robot = 0;
			traverse(pickup_points[pick_point], drop_points_green[drop_point_green]);
			if (flagdg == 0)
			{
				left_turn_wls();
				flagdg++;
			}
			place();
			cout << "rakh diya";
			dir_robot = 1;

			updated_point = drop_points_green[drop_point_green];
			drop_point_green++;
			pick_point++;
			//forward_wls(1);
			//left_turn_wls();
			object++;

		}
		if (color == 2)
		{
			dir_robot = 0;
			cout << "red";
			//int *path = graphInit( pickup_points[pick_point],drop_points_green[drop_point_green]);
			traverse(pickup_points[pick_point], drop_points_red[drop_point_red]);
			if (flagdr == 0)
			{

				flagdr++;
			}
			if (flagdr == 1)
			{
				left_turn_wls();
				flagdr++;
			}
			//right_turn_wls();
			place();
			//cout << "rakh diya";
			//right_turn_wls();
			//right_turn_wls();
			//right_turn_wls();
			dir_robot = 1;


			updated_point = drop_points_red[drop_point_red];
			cout << "updated point: " << updated_point << endl;
			drop_point_red++;
			pick_point++;
			object++;

		}
		if (color == 3)
		{
			cout << "nothing";
			stop();
			dir_robot = 0;
			updated_point = pickup_points[pick_point];
			pick_point++;


			//traverse(drop_points_green[drop_point_green], start);
			//drop_point_green++;

		}

	}
	traverse(updated_point, 1);
	forward_wls(1);
	right_turn_wls();
	stop();
	_delay_ms(3000);

}