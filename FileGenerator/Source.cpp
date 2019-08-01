#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdlib.h>
#include <sstream>
#include <future>
#include <vector>

#define PARENT_DIR "X:\\PARENT_0\\PARENT_4 "
#define NUMBER_OF_THREADS 1
#define MIN_NUMBER_OF_FILES_PER_DIR 20
#define MIN_DEPTH 2

namespace fs = std::filesystem;
using namespace std;

vector<string> source_file_list = { "FILE_0", "FILE_1", "FILE_2", "FILE_3", "FILE_4", "FILE_5", "FILE_6", "FILE_7",  "FILE_8", "FILE_9", "FILE_10" };

void create_directory(std::string& dir_path)
{
	try
	{
		fs::create_directories(dir_path);
		std::cout << "\nDirectory created:" << dir_path << endl;
	}
	catch (exception& e)
	{
		cout << "\n Failed to create directory:" << dir_path << " Reason:" << e.what() << "\n";
	}
}

void copy_file(std::string& dir_path, std::string& tartget_fileName, std::string& source_file_dir)
{
	std::string target_file_path, source_file_path;
	try
	{
		target_file_path = dir_path + "\\" + tartget_fileName;

		int random_number = rand() % 10;
		source_file_path = source_file_dir + "\\" + source_file_list[random_number];

		//std::cout << "\nSource file path:" << source_file_path << endl;
		//std::cout << "\nTarget file path:" << target_file_path << endl;
		fs::copy(source_file_path, target_file_path);
	}
	catch (exception& e)
	{
		cout << "\n Failed to copy file source file:" << source_file_path << " to target file path:" << target_file_path << " Reason:" << e.what() << "\n";
	}
}

void create_files(std::string& dir_path, std::string &source_file_dir)
{
	int random_number = rand() % 25 +  MIN_NUMBER_OF_FILES_PER_DIR;
	stringstream ss;
	string file_name;
	//cout << "\n Number of files to be created:" << random_number << "\n";
	for (int i = 0; i < random_number; i++) 
	{
		ss << "FILE_" << i;
		file_name = ss.str();
		copy_file(dir_path, file_name, source_file_dir);
		ss.str("");
	}
}

int generate_data(std::string parent_dir_path, std::string source_file_dir)
{
	stringstream ss, ss1;
	create_directory(parent_dir_path);

	int depth = rand() % 3 + MIN_DEPTH;
	//cout << "\n Current dir depth:" << depth << endl;

	for (int i = 0; i < depth; i++)
	{
		
		//cout << "\n Current depth:" << width << endl;
		std::string current_dir_path = parent_dir_path;

		ss << current_dir_path << "\\" << "ISM_SUB_" << i;
		current_dir_path = ss.str();
		create_directory(current_dir_path);
		//cout << "Creating files for:" << current_dir_path << endl;
		create_files(current_dir_path, source_file_dir);

		ss1 << current_dir_path;
		int width = rand() % 10 + MIN_DEPTH;

		for (int j = 0; j < width; j++)
		{
			ss1 <<  "\\" << "ISM_CHILD_" << j;
			current_dir_path = ss1.str();
			create_directory(current_dir_path);
			//cout << "Creating files for:" << current_dir_path << endl;
			create_files(current_dir_path, source_file_dir);
		}

		ss.str("");
		ss1.str("");
	}

	return 0;
}

int main()
{
	stringstream ss, ss1;

	std::vector<std::future<int>> futures;

	for (int i = 0; i < NUMBER_OF_THREADS; ++i)
	{
		ss << PARENT_DIR << "PARENT_" << i;
		ss1 << "c:\\SOURCE_DIR_" << i;

		std::string parent_dir_path = ss.str();
		std::string source_dir_path = ss1.str();
		
		futures.push_back(std::async(generate_data, parent_dir_path, source_dir_path));
		ss1.str("");
		ss.str("");
	}

	//retrive and print the value stored in the future
	for (auto& e : futures) {
	   std::cout << e.get() << std::endl;
	}
}