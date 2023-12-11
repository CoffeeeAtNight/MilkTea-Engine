#include "Chaibus.h"

void ChaiBus::subscribe(
	const std::string& eventName,
	std::function<void(ChaiEvent& event)> callback
) {
	try {
		// Try to add the callback for the subscriber to the list
		subscribers[eventName].push_back(callback);
	}
	catch (const std::bad_alloc& e) {
		// Handle specific memory allocation failures
		std::cerr << "Memory allocation error during subscription: " << e.what() << '\n';
	}
	catch (const std::exception& e) {
		// Handle all other standard exceptions
		std::cerr << "Error during subscription: " << e.what() << '\n';
	}
	catch (...) {
		// Catch all other exceptions
		std::cerr << "An unknown error occurred during subscription.\n";
	}
}

void ChaiBus::publish(ChaiEvent& event)
{
	std::cout << "\nPUBLISH CALLED!\n";
	auto& subs = subscribers[event.name]; // Gets all callback functions 

	std::cout << "\nNumber of subscribers: " << subs.size() << "\n";

	for (auto& sub : subs)
	{
		try
		{
			sub(event); // Attempts to call the subscriber's callback
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error during event handling: " << e.what() << "\n";
			// Handle the error (log, recover, etc.)
		}
		catch (...)
		{
			std::cerr << "An unknown error occurred during event handling.\n";
			// Handle the error (log, recover, etc.)
		}
	}
}
