#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : 
    mem(),
    capacity_( capacity ), 
    cur_data_len (0),
    total_pushed_data (0),
    total_poped_data (0),
    closed_(false),
    error_(false) {};
void Writer::push( string data )
{

  (void)data; 

  if(has_error())
      return;
  if(is_closed())
      return;

  const uint64_t push_len = data.length();

  if(push_len > capacity_ - cur_data_len){

      uint64_t actual_len = capacity_ - cur_data_len;
      for(uint64_t i = 0 ; i < actual_len ; i++){
          mem.push(data.at(i));
      }
      total_pushed_data += actual_len;
      cur_data_len = capacity_;

  }else{

      for(uint64_t i = 0 ; i < push_len ; i++){
        mem.push(data.at(i));
      }
      total_pushed_data += push_len;
      cur_data_len += push_len;
  }


  
}

void Writer::close()
{
  closed_ = true;
}

bool Writer::is_closed() const
{
  return closed_; // Your code here.
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - cur_data_len; // Your code here.
}

uint64_t Writer::bytes_pushed() const
{
  return total_pushed_data; // Your code here.
}

string_view Reader::peek() const
{
  
  if(has_error() || mem.empty())
      return string("");

  return string_view(&mem.front(),1); // Your code here.
}

void Reader::pop( uint64_t len )
{
  if(has_error())
      return;



  (void)len; // Your code here.

  uint64_t pop_len = min(len, cur_data_len);

  for(uint64_t i = 0 ; i < pop_len  ; i++){
    mem.pop();
  }

  cur_data_len -= pop_len;
  total_poped_data += pop_len;



}

bool Reader::is_finished() const
{
  return closed_ && cur_data_len == 0; // Your code here.
}

uint64_t Reader::bytes_buffered() const
{
  return cur_data_len; // Your code here.
}

uint64_t Reader::bytes_popped() const
{
  return total_poped_data; // Your code here.
}

