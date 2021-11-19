#include <unordered_map>
#include <functional>
#include <iostream>
#include <vector>

template<typename ... Args>
class EventEmitter {
public:
	EventEmitter() {}
	~EventEmitter() {}

	void on(const std::string& event, const std::function<void(Args && ...)>& handler) {
		
		events[event].emplace_back(handler);

	}

	void emit(const std::string& event, Args && ... args) {
		
		// std::cout << "[DEBUG] triggering: " << event << " with arguments: ";
		// (std::cout << ... << args);
		// std::cout << std::endl;

		auto search = this->events.find(event);
		
		if (search != this->events.end()) {

			for (auto& handler : (search->second)) {
				handler(args...);
			}

		}

	}

private:

	std::unordered_map<std::string, std::vector<std::function<void(Args && ...)>>> events;

};

int main(int argv, const char* arc[]) {

	// -------------------------------------------------

	EventEmitter e0;

	e0.on("EventType1", []() {
		std::cout << "event fired" << std::endl;
	});

	e0.emit("EventType1");

	// -------------------------------------------------

	EventEmitter<const std::string&> e1;

	e1.on("EventType1", [](const std::string& str) {
		std::cout << "event fired with param: " << str << std::endl;
	});

	e1.emit("EventType1", "one");

	// -------------------------------------------------

	EventEmitter<const std::string&, const std::string&> e2;

	e2.on("EventType1", [](const std::string& str1, const std::string& str2) {
		std::cout << "event fired with params: " << str1 << ", " << str2 << std::endl;
	});

	e2.emit("EventType1", "one", "two");

	// -------------------------------------------------

	return 0;

}