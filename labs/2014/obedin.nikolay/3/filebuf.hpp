#ifndef FILEBUF_HPP
#define FILEBUF_HPP

#include <streambuf>
using namespace std;

#include "types.hpp"
#include "filesystem.hpp"


class ofilebuf: public streambuf {

public:
    explicit ofilebuf(filesystem *fs)
        : m_fs(fs), m_cur_block_num(fs->next_free_block_num())
        , m_buffer_size(fs->block_size()-sizeof(block_num))
        , m_buffer(new char[m_buffer_size])
        { setp(m_buffer, m_buffer+(m_buffer_size-1)); }

    virtual ~ofilebuf()
        { sync(); delete[] m_buffer; }

protected:
    filesystem *m_fs;
    block_num m_cur_block_num;
    int m_buffer_size;
    char *m_buffer;

    int flush();
    virtual int overflow(int c);

    virtual int sync()
        { return (flush() == EOF) ? -1 : 0; }

private:
    ofilebuf(const ofilebuf &);
    ofilebuf &operator=(const ofilebuf &);
};


#endif /* end of include guard: FILEBUF_HPP */
