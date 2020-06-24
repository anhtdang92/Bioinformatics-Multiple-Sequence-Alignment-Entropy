// Bioinformatics - Assignment 3
// By: Anh Dang

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

float displayProfile(char char_seq[100][100], int num_of_seq, int seq_len)
{
	float acgt[100][5] = { 0 };
	// count ACGT-
	for (int x = 0; x < num_of_seq; x++)
	{
		for (int y = 0; y < seq_len; y++)
		{
			if (char_seq[x][y] == 'A' || char_seq[x][y] == 'a')
			{
				acgt[y][0]++;
			}
			if (char_seq[x][y] == 'C' || char_seq[x][y] == 'c')
			{
				acgt[y][1]++;
			}
			if (char_seq[x][y] == 'G' || char_seq[x][y] == 'g')
			{
				acgt[y][2]++;
			}
			if (char_seq[x][y] == 'T' || char_seq[x][y] == 't')
			{
				acgt[y][3]++;
			}
			if (char_seq[x][y] == '-')
			{
				acgt[y][4]++;
			}
		}
	}
	// print matrix
	cout << "============" << endl;
	cout << "Input matrix" << endl;
	cout << "============" << endl;
	cout << "A ";
	for (int x = 0; x < seq_len; x++)
	{
		cout << acgt[x][0] << " ";
	}
	cout << endl;
	cout << "C ";
	for (int x = 0; x < seq_len; x++)
	{
		cout << acgt[x][1] << " ";
	}
	cout << endl;
	cout << "G ";
	for (int x = 0; x < seq_len; x++)
	{
		cout << acgt[x][2] << " ";
	}
	cout << endl;
	cout << "T ";
	for (int x = 0; x < seq_len; x++)
	{
		cout << acgt[x][3] << " ";
	}
	cout << endl;
	cout << "- ";
	for (int x = 0; x < seq_len; x++)
	{
		cout << acgt[x][4] << " ";
	}
	cout << endl;

	// print profile in decimals
	cout << "========================" << endl;
	cout << "Input profile in decimal" << endl;
	cout << "========================" << endl;
	cout << "A ";
	for (int x = 0; x < seq_len; x++)
	{
		cout << acgt[x][0] / num_of_seq << " ";
	}
	cout << endl;
	cout << "C ";
	for (int x = 0; x < seq_len; x++)
	{
		cout << acgt[x][1] / num_of_seq << " ";
	}
	cout << endl;
	cout << "G ";
	for (int x = 0; x < seq_len; x++)
	{
		cout << acgt[x][2] / num_of_seq << " ";
	}
	cout << endl;
	cout << "T ";
	for (int x = 0; x < seq_len; x++)
	{
		cout << acgt[x][3] / num_of_seq << " ";
	}
	cout << endl;
	cout << "- ";
	for (int x = 0; x < seq_len; x++)
	{
		cout << acgt[x][4] / num_of_seq << " ";
	}
	cout << endl;

	// compute entropy score
	float entropy = 0;

	for (int x = 0; x < seq_len; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			if ((acgt[x][y] / num_of_seq) != 0)
			{
				entropy += (acgt[x][y] / num_of_seq) * (log2(acgt[x][y] / num_of_seq));
			}
		}
	}
	cout << "-----------------------" << endl;
	cout << "Entropy score is: " << -entropy << endl;
	
	return (-1)*entropy;

}
void sequenceInput()
{
	fstream sequence;
	sequence.open("sequence3.txt");

	string arr[100];

	int second_seq_pos;

	for (int x = 0; x < 100; x++)
	{
		sequence >> arr[x];// store sequence in string array

		if (arr[x] == "#")
		{
			second_seq_pos = x;// position of #, array starting at 0
		}
	}
	int alignment_1_len = arr[0].length();// compute length of alignment 1
	int alignment_2_len = arr[second_seq_pos + 1].length();// compute length of alignment 2
	
	cout << "==================" << endl;
	cout << "Input sequence #1:" << endl;
	cout << "==================" << endl;

	char sequenceArr_1[100][100];// max char array 100x100
	char sequenceArr_2[100][100];
	// store first sequence in array
	for (int x = 0; x < second_seq_pos; x++)
	{
		for (int y = 0; y < alignment_1_len; y++)
		{
			strcpy_s(sequenceArr_1[x], arr[x].c_str());
			cout << sequenceArr_1[x][y];
		}
		cout << endl;
	}
	cout << "------------------" << endl;
	cout << "Sequence Length: " << second_seq_pos << endl;
	// store second sequence in array
	int total_num_seq = second_seq_pos * 2;

	cout << "==================" << endl;
	cout << "Input sequence #2:" << endl;
	cout << "==================" << endl;
	
	int start_of_second_seq = second_seq_pos + 1;
	
	for (int x = start_of_second_seq; x < total_num_seq + 1; x++)
	{
		for (int y = 0; y < alignment_2_len; y++)
		{
			strcpy_s(sequenceArr_2[x-start_of_second_seq], arr[x].c_str());
			cout << sequenceArr_2[x-start_of_second_seq][y];
		}
		cout << endl;
	}

	cout << "------------------" << endl;
	cout << "Sequence Length: " << total_num_seq - second_seq_pos << endl;
	cout << "--------------------------" << endl;
	cout << "Total number of sequence: " << total_num_seq << endl;//total number of sequences not including #

	// compute better alignment

	float entropy_1 = displayProfile(sequenceArr_1, total_num_seq / 2, alignment_1_len);
	float entropy_2 = displayProfile(sequenceArr_2, total_num_seq / 2, alignment_2_len);
	if (entropy_1 < entropy_2)
	{
		cout << "======================" << endl;
		cout << "Alignment 1 is better." << endl;
		cout << "======================" << endl;
	}
	if (entropy_1 > entropy_2)
	{
		cout << "======================" << endl;
		cout << "Alignment 1 is better." << endl;
		cout << "======================" << endl;
	}
	if (entropy_1 == entropy_2)
	{
		cout << "======================================" << endl;
		cout << "Alignment 1 & 2 have the same entropy." << endl;
		cout <<	"======================================" << endl;
	}

}

int main()
{
	sequenceInput();
	system("PAUSE");
	return 0;
}