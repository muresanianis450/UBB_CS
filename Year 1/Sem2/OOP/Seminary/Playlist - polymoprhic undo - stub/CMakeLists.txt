cmake_minimum_required(VERSION 3.30)
project(Playlist___polymoprhic_undo___stub)

set(CMAKE_CXX_STANDARD 14)

include_directories(Playlist)

add_executable(Playlist___polymoprhic_undo___stub
    Playlist/Action.cpp
    Playlist/Action.h
    Playlist/ActionAdd.cpp
    Playlist/ActionAdd.h
    Playlist/ActionRemove.cpp
    Playlist/ActionRemove.h
    Playlist/ActionUpdate.cpp
    Playlist/ActionUpdate.h
    Playlist/CSVPlaylist.cpp
    Playlist/CSVPlaylist.h
    Playlist/FilePlaylist.cpp
    Playlist/FilePlaylist.h
    Playlist/main.cpp
    Playlist/PlayList.cpp
    Playlist/PlayList.h
    Playlist/Repository.cpp
    Playlist/Repository.h
    Playlist/RepositoryExceptions.cpp
    Playlist/RepositoryExceptions.h
    Playlist/Service.cpp
    Playlist/Service.h
    Playlist/Song.cpp
    Playlist/Song.h
    Playlist/SongValidator.cpp
    Playlist/SongValidator.h
    Playlist/UI.cpp
    Playlist/UI.h
    Playlist/Utils.cpp
    Playlist/Utils.h)
