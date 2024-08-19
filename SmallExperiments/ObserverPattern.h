#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Event
{
public:
	std::string discription;
};

class Observor
{
public:
	virtual void Update(const Event& e) = 0;
};

class Subject
{
public:
	Subject() = default;
	void AddObservor(Observor* obs) {
		observors.push_back(obs);
	}
	void RemoveObservor(Observor* obs) {
		std::erase(observors, obs);
	}
	void Notify(const Event& e) {
		for (auto obs : observors) {
			obs->Update(e);
		}
	}
private:
	std::vector<Observor*> observors;
};



class YoutubeChannel : public Subject {
public:
	YoutubeChannel(const std::string& name)
		: name(name)
	{}
	void UploadVideo(const std::string& title) {
		Event e{ name + " uplaoded video with title: " + title };
		std::cout << e.discription << '\n';
		Notify(e);
	}
	std::string GetName() const {
		return name;
	}
private:
	std::string name;
};

class YoutubeUser : public Observor {
public:
	YoutubeUser(const std::string& name)
		: name(name)
	{}
	void Update(const Event& e) override {
		Notify(e);
	}

	void Notify(const Event& e) {
		std::cout << "Notification sent to " << name << ": \"" << e.discription << "\"\n";
	}
	void Subscribe(YoutubeChannel& channel) {
		channel.AddObservor(this);
		Event e{ "You've been subcribed to channel " + channel.GetName() };
		Notify(e);
	}
private:
	std::string name;
};

void Test() {
	YoutubeChannel myChannel("ShannuBoi");
	YoutubeUser subscriber1("Shayan");
	YoutubeUser subscriber2("Hassaan");
	YoutubeUser subscriber3("Salman");

	subscriber1.Subscribe(myChannel);
	subscriber2.Subscribe(myChannel);

	std::cout << '\n';

	myChannel.UploadVideo("My response to the drama... (Watch till the end)");

	std::cout << '\n';

	subscriber3.Subscribe(myChannel);

	std::cout << '\n';

	myChannel.UploadVideo("CRAZY Pregnancy Prank (GONE WRONG)");

	std::cout << '\n';
}