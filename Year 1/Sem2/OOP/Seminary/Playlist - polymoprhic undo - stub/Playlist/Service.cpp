#include "Service.h"
#include <algorithm>
#include "FilePlaylist.h"
#include "RepositoryExceptions.h"
#include "ActionAdd.h"
#include "ActionRemove.h"
#include "ActionUpdate.h"

using namespace std;

void Service::addSongToRepository(const std::string& artist, const std::string& title, double minutes, double seconds, const std::string& source)
{
	Song s{ artist, title, Duration{minutes, seconds}, source };
	this->validator.validate(s);
	this->repo.addSong(s);

	this->undoStack.push(std::make_unique<AddAction>(this->repo, s));
	while (!this->redoStack.empty()) this->redoStack.pop(); // Clear redo stack

}

void Service::removeSongFromRepository(const std::string & artist, const std::string & title)
{
	Song s = this->repo.findByArtistAndTitle(artist, title);
	this->repo.removeSong(s);

	this->undoStack.push(std::make_unique<RemoveAction>(this->repo, s));
	while (!this->redoStack.empty()) this->redoStack.pop(); // Clear redo stack

}

void Service::updateSong(const std::string &artist, const std::string &title, double minutes, double seconds, const std::string& source){
	Song oldSong = this->repo.findByArtistAndTitle(artist, title);
    Song newSong{ artist, title, Duration{minutes, seconds}, source };
    this->validator.validate(newSong);
    this->repo.updateSong(newSong);

    this->undoStack.push(std::make_unique<UpdateAction>(this->repo, oldSong, newSong));
    while (!this->redoStack.empty()) this->redoStack.pop();
}


void Service::undo() {
	if (this->undoStack.empty()) throw std::runtime_error("No actions to undo!");
	auto action = std::move(this->undoStack.top());
	this->undoStack.pop();
	action->executeUndo();
	this->redoStack.push(std::move(action));
}

void Service::redo() {
	if (this->redoStack.empty()) throw std::runtime_error("No actions to redo!");
	auto action = std::move(this->redoStack.top());
	this->redoStack.pop();
	action->executeRedo();
	this->undoStack.push(std::move(action));
}


void Service::addSongToPlaylist(const Song& song)
{
	if (this->playList == nullptr)
		return;
	this->playList->add(song);
}

void Service::addAllSongsByArtistToPlaylist(const std::string& artist)
{
	vector<Song> songs = this->repo.getSongs();
	int nSongs = static_cast<int>(count_if(songs.begin(), songs.end(),
		[artist](const Song& s)
		{
			return s.getArtist() == artist;
		}));

	vector<Song> songsByArtist(nSongs);
	copy_if(songs.begin(), songs.end(), songsByArtist.begin(),
		[artist](const Song& s)
		{
			return s.getArtist() == artist;
		});

	for (auto s : songsByArtist)
		this->playList->add(s);
}

void Service::startPlaylist()
{
	if (this->playList == nullptr)
		return;
	this->playList->play();
}

void Service::nextSongPlaylist()
{
	if (this->playList == nullptr)
		return;
	this->playList->next();
}

void Service::savePlaylist(const std::string& filename)
{
	if (this->playList == nullptr)
		return;

	this->playList->setFilename(filename);
	this->playList->writeToFile();
}

void Service::openPlaylist() const
{
	if (this->playList == nullptr)
		return;

	this->playList->displayPlaylist();
}
