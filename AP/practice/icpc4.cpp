#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int> > board;
void full_vec(board &vec, int step, int i, int j, int n, int number)
{
    // int i, j;
    switch (step)
    {
    case 0:
        for (; j < n; j++)
        {
            if (vec.at(i).at(j) == -1)
            {
                vec.at(i).at(j) = number+1;
                number++;
                if (number == n * n)
                    return;
            }
            else
            {
                break;
            }
        }
        j--;
        i--;
        break;
    case 1:
        for (; i > -1; i--)
        {
            if (vec.at(i).at(j) == -1)
            {
                vec.at(i).at(j) = number+1;
                number++;
                if (number == n * n)
                    return;
            }
            else
            {
                break;
            }
        }
        i++;
        j--;
        break;
    case 2:
        for (; j > -1; j--)
        {
            if (vec.at(i).at(j) == -1)
            {
                vec.at(i).at(j) = number+1;
                number++;
                if (number == n * n)
                    return;
            }
            else
            {
                break;
            }
        }
        j++;
        i++;
        break;
    case 3:
        for (; i < n; i++)
        {
            if (vec.at(i).at(j) == -1)
            {
                vec.at(i).at(j) = number+1;
                number++;
                if (number == n * n)
                    return;
            }
            else
            {
                break;
            }
        }
        i--;
        j++;
        break;
    }
    if (number == n * n)
        return;
    step = (step + 1) % 4;
    full_vec(vec, step, i, j, n, number);
}
int get_index(int current_index_i,int current_index_j, int target_index_i,int target_index_j)
{
    int delta_x = target_index_i - current_index_i;
    int delta_y = target_index_j - current_index_j;
    if (delta_x<0)
    {
        cout << -1*delta_x <<'L'<<endl;
    }
    else if (delta_x == 0 )
    {
        cout <<endl;
    }
    else if(delta_x >0)
    {
        cout << delta_x <<'R'<<endl;
    }
    if (delta_y<0)
    {
        cout << -1*delta_y <<'U'<<endl;
    }
    else if (delta_y == 0 )
    {
        cout <<endl;
    }
    else if(delta_y >0)
    {
        cout << delta_y <<'D'<<endl;
    }

    
}
void findd(int& i , int& j, int d){

}
int main()
{

    int n, s, d;
    int step = 0;
    cin >> n >> s>> d;
    int num = 0;
    int i = n - 1, j = 0;
    board vec(n, vector<int>(n, -1));
    full_vec(vec, step, i, j, n, num);
    for (int k = 0; k < n; k++)
    {
        for (int w = 0; w < n; w++)
            cout << vec[k][w] << ' ';
        cout << endl;
    }
    findd(i , j , d);
}
