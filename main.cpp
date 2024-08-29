
#include <bits/stdc++.h>
#include <cstdlib> 
using namespace std;

#define endl '\n'
using lli=long long int;
const lli MOD=1e9+7;
using ii=pair<int,int>;
#define F first
#define S second

void print_grid(vector<vector<int>> &arr){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            cout<<arr[i][j]<<" ";
        }cout<<endl;
    }

    cout<<endl;
    return;
}

vector<vector<int>> move(int i, int j, vector<vector<int>> grid) {
    // Calculate the size of the square (n)
    int n = min(i + 1, j + 1);

    // Invert all values in the n x n square with bottom-right corner at (i, j)
    for (int row = i - n + 1; row <= i && row>=0; ++row) {
        for (int col = j - n + 1; col <= j && j>=0; ++col) {
            grid[row][col] = 1 - grid[row][col];  // Invert the value (0 -> 1, 1 -> 0)
        }
    }

    return grid;
}

vector<vector<int>> integerTo4x4BinaryGrid(int x) {
    // Convert the integer to a 16-bit binary string
    bitset<16> binary(x);

    // Prepare a 4x4 grid
    vector<vector<int>> grid(4, vector<int>(4));

    // Fill the grid with the binary values
    for (int i = 0; i < 16; ++i) {
        grid[i / 4][i % 4] = binary[15 - i];
    }

    return grid;
}

int binaryGridToInteger(const vector<vector<int>>& grid) {
    bitset<16> binary;

    for (int i = 0; i < 16; ++i) {
        binary[15 - i] = grid[i / 4][i % 4];
    }

    return static_cast<int>(binary.to_ulong());
}

bool isValid(int i, int j, vector<vector<int>> &grid) {
    if(grid[i][j]==0){
        return false;
    }
    return true;
}

vector<ii> find_ones(int num){
    vector<ii> output;
    vector<vector<int>> temp=integerTo4x4BinaryGrid(num);
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(temp[i][j])output.push_back({i+1,j+1});
        }
    }
    return output;
}

int calc(int x, int y){
	if(!x)
		return 0;
	return calc(y % x, x) ^ ((y / x) & 1);
}

int f(int x, int y){
	return calc(x, y) ^ calc(x - 1, y) ^ calc(x, y - 1) ^ calc(x - 1, y - 1);
}

bool is_winning(int num){
    int ans=0;
    vector<ii> ones=find_ones(num);
    for(auto v:ones){
        int x=v.F; int y=v.S;
        ans^=f(x,y);
    }
    return ans;
}

vector<vector<int>> computer_turn(int num, vector<vector<int>> grid){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(grid[i][j]==1){
                vector<vector<int>> new_grid=move(i,j,grid);
                int new_num=binaryGridToInteger(new_grid);
                if(!is_winning(new_num)){
                    cout<<"Computer chose optimally: row = "<<i+1<<" col = "<<j+1<<endl;
                    return new_grid;
                }
            }
        }
    }
    return grid;
}

void solve(){
    cout<<"Write any number between 1 and 2^15"<<endl;
    int num; cin>>num;
    vector<vector<int>> grid=integerTo4x4BinaryGrid(num);
    print_grid(grid);

    bool turn=true;
    while(num!=0){
        if(turn){
            cout<<"Your Turn: Choose a row and column of a black cell i.e 1 and consider 1 based-indexing"<<endl;
            int row,col; cin>>row>>col;
            row--; col--;
            if(!isValid(row,col,grid)){
                cout<<"Wrong move"<<endl;
                continue;
            }else{
                vector<vector<int>> new_grid=move(row,col,grid);
                grid=new_grid;
                num=binaryGridToInteger(new_grid);
                print_grid(new_grid);
                turn=false;
            }
        }else{
            cout<<"Computer's turn"<<endl;

            if(is_winning(num)){
                vector<vector<int>> new_grid=computer_turn(num,grid);
                grid=new_grid;
                num=binaryGridToInteger(new_grid);
                print_grid(new_grid);
                turn=true;
            }else{
                vector<ii> ones=find_ones(num);
                int index=rand()%(ones.size());
                int i=ones[index].F-1,j=ones[index].S-1;
                vector<vector<int>> new_grid=move(i,j,grid);
                cout<<"Computer chose randomly: row = "<<i+1<<" col = "<<j+1<<endl;
                grid=new_grid;
                num=binaryGridToInteger(new_grid);
                print_grid(new_grid);
                turn=true;
            }
        }
    }
    if(turn){
        cout<<"You Lost :(((("<<endl;
    }else{
        cout<<"You Won :))))"<<endl;
    }
}

signed main(){
    char q='\0';
    while(q!='q'){
        solve();
        cout<<"Press any key to continue. Press q to exit..."<<endl;
        cin>>q;
    }
}