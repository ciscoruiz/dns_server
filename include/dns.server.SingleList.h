#ifndef _dns_server_SingleSingleList_h
#define _dns_server_SingleSingleList_h

namespace dns {

namespace server {

template <typename _T> class SingleList {
public:
   struct Node {
      _T* data;
      Node* next;

      Node (_T* _data) :  data (_data), next (NULL) {;}
      ~Node () { delete data; delete next; }
   };

   typedef Node* iterator;

   SingleList () : head (NULL), tail (NULL) {;}
   virtual ~SingleList () { delete head; }

   void push_back (_T* data) throw () {
      if (head == NULL) {
         tail = head = new Node (data);
      }
      else {
         Node* newNode = new Node (data);
         tail->next = newNode;
         tail = newNode;
      }
   }

   iterator begin () throw () { return head; }

   static iterator next (iterator ii) throw () { return ii->next; }

private:
   Node* head;
   Node* tail;
};

}
}

#endif

