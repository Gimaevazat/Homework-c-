#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "visualizer.h"

int main(int argc, char** argv)
{
	float a = -0.8;
	float b = 0.156;
	int n = 100;

	for (int i = 1; i < n; i++) {
		float c = - 1.5 + i*static_cast <float>(1) / static_cast <float> (n);
		try
		{
			Visualizer visualizer;

			visualizer.screenshot(c, b);
			std::string way = "screenshots\\" + std::to_string(i) + ".png";
			visualizer.save(way);
		}
		catch (const std::exception& exception)
		{
			std::cerr << exception.what() << '\n';

			system("pause");

			return EXIT_FAILURE;
		}
		catch (...)
		{
			std::cerr << "Unknown exception\n";

			system("pause");

			return EXIT_FAILURE;
		}
	}
	/*
	try
	{
		Visualizer visualizer;

		visualizer.run(a, b);
		
	}
	catch (const std::exception& exception)
	{
		std::cerr << exception.what() << '\n';

		system("pause");

		return EXIT_FAILURE;
	}
	catch (...)
	{
		std::cerr << "Unknown exception\n";

		system("pause");

		return EXIT_FAILURE;
	}
	*/
	system("pause");

	return EXIT_SUCCESS;
}