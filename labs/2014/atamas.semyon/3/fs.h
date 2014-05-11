#ifndef FS_H
#define FS_H

#include <string>
#include <time.h>
#include <vector>
#include <iostream>
#include <iterator>
#include "structs.h"

class DirIterator;

class FS {

public:
    FS(std::string root);
    ~FS();

    void init();
    void format();
    void import(std::string host_file, std::string fs_file);
    void fexport(std::string fs_file, std::string host_file);
    void copy(std::string src, std::string dest);
    void ls(std::string filename);
    void mkdir(std::string path);
    void move(std::string src, std::string dst);
    void rm(std::string path);


private:
    void copy(FileDescriptor src, FileDescriptor dest_file);
    void rm(FileDescriptor file);
    Config read_config();
    Meta meta;
    FileDescriptor root_descriptor;
    bool initialized;
    std::string _root;
    const Config config;
    std::vector<Block *> blocks;
    std::string get_block_name(int block_id);
    Block  * get_block(int i){
    	if( blocks[i] == 0){
    		blocks[i] = new Block(i, config.block_size);
    		return blocks[i];
    	}else{
    		return blocks[i];
    	}
    }
    Block  * get_block(int i, std::string root){
    	if( blocks[i] == 0){
    		blocks[i] = new Block(i, config.block_size, root);
    		return blocks[i];
    	}else{
    		return blocks[i];
    	}
    }

    FileDescriptor get_file(std::string path, bool create, bool file_available);
    void free_block(int n);
    void reserve_block(int n);
    void write_data(void * data, int size, Block * first_block);
    void read_data(void * data, int size, Block * first_block);
    void write_meta();
    void read_meta();
    void update_descriptor(FileDescriptor & fd, Block * block);
    Block * get_free_block();
    friend class DirIterator;
};

class DirIterator: std::iterator<std::forward_iterator_tag, FileDescriptor>{
public:
	DirIterator(FS & fs):
	_fs(fs){
		p = 0;
	}
	DirIterator(FS & fs, FileDescriptor dir);
	DirIterator& operator++();
	DirIterator operator++(int) {DirIterator tmp(*this); operator++(); return tmp;}
	bool operator==(const DirIterator& rhs) {return p->filename==rhs.p->filename;}
	bool operator!=(const DirIterator& rhs) {return p->filename!=rhs.p->filename;}
	FileDescriptor& operator*() {return *p;}
private:
	FileDescriptor * p;
	FS & _fs;
};

#endif // FS_H
