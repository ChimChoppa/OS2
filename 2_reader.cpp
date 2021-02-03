#include <pch.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <locale.h>

using namespace std;


int main()
{
	HANDLE handleMap;
	string descriptorName;
	LPVOID mapView;


	cout << "Enter descriptor name (same as in writer program): " << endl;
	cin >> descriptorName;


	handleMap = OpenFileMapping(FILE_MAP_READ, false, (LPCWSTR)descriptorName.c_str());

	if (handleMap)
	{
		//Создает mapView, чтобы отобразить представления проецируемого файла в адресном пространстве

		mapView = MapViewOfFile(handleMap, FILE_MAP_READ, 0, 0, NULL);
		if (mapView)
		{
			//Выводит информацию из файла

			cout << "File data:" << endl
				<< (char*)mapView << endl;
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
		cout << " An error occurred in OpenFileMapping. Error code: " << GetLastError() << endl;
		system("pause");

	}

	if (handleMap) {
		CloseHandle(handleMap);
	}

	return 0;
}
