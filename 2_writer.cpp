#include <pch.h>
#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;


int main() {

	string fileDirection, descriptorName, writingData;

	HANDLE handleFile, handleMap;

	LPVOID mapView;


	// Создаем файл

	cout << " Enter direction of file (example c://newDir//newFile.txt): " << endl;
	cin >> fileDirection;


	handleFile = CreateFileA((LPCSTR)fileDirection.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ,

		NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (handleFile)
	{
		cout << " File " << fileDirection << " was created successful." << endl;

		// Создаем map

		cout << "Enter descriptor name: " << endl;
		cin >> descriptorName;




		handleMap = CreateFileMapping(handleFile, NULL, PAGE_READWRITE, 0, 512, (LPCWSTR)descriptorName.c_str());

		if (handleMap) {


			// Создает mapView, чтобы отобразить представления проецируемого файла в адресном пространстве
			mapView = MapViewOfFile(handleMap, FILE_MAP_WRITE, 0, 0, NULL);
			if (mapView)
			{

				// Вводим строку и записываем ее в файл

				cout << "Enter the string which must be written to a file: " << endl;

				cin.ignore(1024, '\n');
				getline(cin, writingData);

				CopyMemory(mapView, (char*)writingData.c_str(), writingData.length() * sizeof(char));

				cout << "String written successful: " << endl;

				system("pause");
				UnmapViewOfFile(mapView);
			}
			else
			{
				cout << " An error occurred in MapViewOfFile. Error code: " << GetLastError() << endl;
				system("pause");

			}


		}
		else
		{
			cout << " An error occurred in CreateFileMappingA. Error code: " << GetLastError() << endl;
			system("pause");

		}
		if (handleFile) {
			CloseHandle(handleFile);
		}
	}

	else
	{
		cout << " An error occurred in CreateFileA. Error code: " << GetLastError() << endl;
		system("pause");
	}

	if (handleFile) {
		CloseHandle(handleFile);
	}

	return 0;
}
