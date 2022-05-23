#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <climits>
#include <functional>
#include <iomanip>
#include <stack>

using namespace std;

#define SET(func_name,type,var_name,_var_name) void func_name(type _var_name) { var_name = _var_name ;} 
#define GET(func_name,type,var_name) type func_name() const { return var_name ;}

class header;
class payload;
class packet;
class node;
class event;
class link; // new

// for simplicity, we use a const int to simulate the delay
// if you want to simulate the more details, you should revise it to be a class
const unsigned int ONE_HOP_DELAY = 10;
const unsigned int BROCAST_ID = UINT_MAX;

// BROCAST_ID means that all neighbors are receivers; UINT_MAX is the maximum value of unsigned int

class header {
    public:
        virtual ~header() {}

        SET(setSrcID, unsigned int , srcID, _srcID);
        SET(setDstID, unsigned int , dstID, _dstID);
        SET(setPreID, unsigned int , preID, _preID);
        SET(setNexID, unsigned int , nexID, _nexID);
        GET(getSrcID, unsigned int , srcID);
        GET(getDstID, unsigned int , dstID);
        GET(getPreID, unsigned int , preID);
        GET(getNexID, unsigned int , nexID);
        
        virtual string type() = 0;
        
        // factory concept: generate a header
        class header_generator {
                // lock the copy constructor
                header_generator(header_generator &){}
                // store all possible types of header
                static map<string,header_generator*> prototypes;
            protected:
                // allow derived class to use it
                header_generator() {}
                // after you create a new header type, please register the factory of this header type by this function
                void register_header_type(header_generator *h) { prototypes[h->type()] = h; }
                // you have to implement your own generate() to generate your header
                virtual header* generate() = 0 ;
            public:
                // you have to implement your own type() to return your header type
        	    virtual string type() = 0 ;
        	    // this function is used to generate any type of header derived
        	    static header * generate (string type) {
            		if(prototypes.find(type) != prototypes.end()){ // if this type derived exists 
            			return prototypes[type]->generate(); // generate it!!
            		}
            		std::cerr << "no such header type" << std::endl; // otherwise
            		return nullptr;
            	}
            	static void print () {
            	    cout << "registered header types: " << endl;
            	    for (map<string,header::header_generator*>::iterator it = prototypes.begin(); it != prototypes.end(); it ++)
            	        cout << it->second->type() << endl;
            	}
            	virtual ~header_generator(){};
        };
        
    protected:
        header():srcID(BROCAST_ID),dstID(BROCAST_ID),preID(BROCAST_ID),nexID(BROCAST_ID){} // this constructor cannot be directly called by users

    private:
        unsigned int srcID;
        unsigned int dstID;
        unsigned int preID;
        unsigned int nexID;
        header(header&){} // this constructor cannot be directly called by users
};
map<string,header::header_generator*> header::header_generator::prototypes;

class SDN_data_header : public header{
        SDN_data_header(SDN_data_header&){} // cannot be called by users
        
    protected:
        SDN_data_header(){} // this constructor cannot be directly called by users

    public:
        ~SDN_data_header(){}
        string type() { return "SDN_data_header"; }

        class SDN_data_header_generator;
        friend class SDN_data_header_generator;
        // SDN_data_header_generator is derived from header_generator to generate a header
        class SDN_data_header_generator : public header_generator{
                static SDN_data_header_generator sample;
                // this constructor is only for sample to register this header type
                SDN_data_header_generator() { /*cout << "SDN_data_header registered" << endl;*/ register_header_type(&sample); }
            protected:
                virtual header * generate(){
                    // cout << "SDN_data_header generated" << endl;
                    return new SDN_data_header; 
                }
            public:
                virtual string type() { return "SDN_data_header";}
                ~SDN_data_header_generator(){}
        
        };
};
SDN_data_header::SDN_data_header_generator SDN_data_header::SDN_data_header_generator::sample;

class SDN_ctrl_header : public header{
        SDN_ctrl_header(SDN_ctrl_header&){} // cannot be called by users
        
    protected:
        SDN_ctrl_header(){} // this constructor cannot be directly called by users

    public:
        ~SDN_ctrl_header(){}
        string type() { return "SDN_ctrl_header"; }

        class SDN_ctrl_header_generator;
        friend class SDN_ctrl_header_generator;
        // SDN_ctrl_header_generator is derived from header_generator to generate a header
        class SDN_ctrl_header_generator : public header_generator{
                static SDN_ctrl_header_generator sample;
                // this constructor is only for sample to register this header type
                SDN_ctrl_header_generator() { /*cout << "SDN_ctrl_header registered" << endl;*/ register_header_type(&sample); }
            protected:
                virtual header * generate(){
                    // cout << "SDN_ctrl_header generated" << endl;
                    return new SDN_ctrl_header; 
                }
            public:
                virtual string type() { return "SDN_ctrl_header";}
                ~SDN_ctrl_header_generator(){}
        
        };
};
SDN_ctrl_header::SDN_ctrl_header_generator SDN_ctrl_header::SDN_ctrl_header_generator::sample;


class payload {
        payload(payload&){} // this constructor cannot be directly called by users
        
        string msg;
        
    protected:
        payload(){}
    public:
        virtual ~payload(){}
        virtual string type() = 0;
        
        SET(setMsg,string,msg,_msg);
        GET(getMsg,string,msg);
        
        class payload_generator {
                // lock the copy constructor
                payload_generator(payload_generator &){}
                // store all possible types of header
                static map<string,payload_generator*> prototypes;
            protected:
                // allow derived class to use it
                payload_generator() {}
                // after you create a new payload type, please register the factory of this payload type by this function
                void register_payload_type(payload_generator *h) { prototypes[h->type()] = h; }
                // you have to implement your own generate() to generate your payload
                virtual payload* generate() = 0;
            public:
                // you have to implement your own type() to return your header type
        	    virtual string type() = 0;
        	    // this function is used to generate any type of header derived
        	    static payload * generate (string type) {
            		if(prototypes.find(type) != prototypes.end()){ // if this type derived exists 
            			return prototypes[type]->generate(); // generate it!!
            		}
            		std::cerr << "no such payload type" << std::endl; // otherwise
            		return nullptr;
            	}
            	static void print () {
            	    cout << "registered payload types: " << endl;
            	    for (map<string,payload::payload_generator*>::iterator it = prototypes.begin(); it != prototypes.end(); it ++)
            	        cout << it->second->type() << endl;
            	}
            	virtual ~payload_generator(){};
        };
};
map<string,payload::payload_generator*> payload::payload_generator::prototypes;


class SDN_data_payload : public payload {
        SDN_data_payload(SDN_data_payload&){}

    protected:
        SDN_data_payload(){} // this constructor cannot be directly called by users
    public:
        ~SDN_data_payload(){}
        
        string type() { return "SDN_data_payload"; }
        
        class SDN_data_payload_generator;
        friend class SDN_data_payload_generator;
        // SDN_data_payload is derived from payload_generator to generate a payload
        class SDN_data_payload_generator : public payload_generator{
                static SDN_data_payload_generator sample;
                // this constructor is only for sample to register this payload type
                SDN_data_payload_generator() { /*cout << "SDN_data_payload registered" << endl;*/ register_payload_type(&sample); }
            protected:
                virtual payload * generate(){ 
                    // cout << "SDN_data_payload generated" << endl;
                    return new SDN_data_payload; 
                }
            public:
                virtual string type() { return "SDN_data_payload";}
                ~SDN_data_payload_generator(){}
        };
};
SDN_data_payload::SDN_data_payload_generator SDN_data_payload::SDN_data_payload_generator::sample;

class SDN_ctrl_payload : public payload {
        SDN_ctrl_payload(SDN_ctrl_payload&){}
        
        unsigned int matID; // match: target
        unsigned int actID; // action: the next hop

    protected:
        SDN_ctrl_payload(){} // this constructor cannot be directly called by users
    public:
        ~SDN_ctrl_payload(){}

        string type() { return "SDN_ctrl_payload"; }
        
        SET(setMatID,unsigned int,matID,_matID);
        GET(getMatID,unsigned int,matID);
        SET(setActID,unsigned int,actID,_actID);
        GET(getActID,unsigned int,actID);
        
        
        class SDN_ctrl_payload_generator;
        friend class SDN_ctrl_payload_generator;
        // SDN_data_payload is derived from payload_generator to generate a payload
        class SDN_ctrl_payload_generator : public payload_generator{
                static SDN_ctrl_payload_generator sample;
                // this constructor is only for sample to register this payload type
                SDN_ctrl_payload_generator() { /*cout << "SDN_ctrl_payload registered" << endl;*/ register_payload_type(&sample); }
            protected:
                virtual payload * generate(){ 
                    // cout << "SDN_ctrl_payload generated" << endl;
                    return new SDN_ctrl_payload; 
                }
            public:
                virtual string type() { return "SDN_ctrl_payload";}
                ~SDN_ctrl_payload_generator(){}
        };
};
SDN_ctrl_payload::SDN_ctrl_payload_generator SDN_ctrl_payload::SDN_ctrl_payload_generator::sample;


class packet{
        // a packet usually contains a header and a payload
        header *hdr;
        payload *pld;
        unsigned int p_id;
        static unsigned int last_packet_id ; 
        
        packet(packet &) {}
        static int live_packet_num ;
    protected:
        // these constructors cannot be directly called by users
        packet(): hdr(nullptr), pld(nullptr) { p_id=last_packet_id++; live_packet_num ++; }
        packet(string _hdr, string _pld, bool rep = false, unsigned int rep_id = 0) {
            if (! rep ) // a duplicated packet does not have a new packet id
                p_id = last_packet_id ++;
            else
                p_id = rep_id;
            hdr = header::header_generator::generate(_hdr); 
            pld = payload::payload_generator::generate(_pld); 
            live_packet_num ++;
        }
    public:
        virtual ~packet(){ 
            // cout << "packet destructor begin" << endl;
            if (hdr != nullptr) 
                delete hdr; 
            if (pld != nullptr) 
                delete pld; 
            live_packet_num --;
            // cout << "packet destructor end" << endl;
        }
        
        SET(setHeader,header*,hdr,_hdr);
        GET(getHeader,header*,hdr);
        SET(setPayload,payload*,pld,_pld);
        GET(getPayload,payload*,pld);
        GET(getPacketID,unsigned int,p_id);
        
        static void discard ( packet* &p ) {
            // cout << "checking" << endl;
            if (p != nullptr) {
                // cout << "discarding" << endl;
                // cout << p->type() << endl;
                delete p;
                // cout << "discarded" << endl;
            }
            p = nullptr;
            // cout << "checked" << endl;
        }
        virtual string type () = 0;
        
        static int getLivePacketNum () { return live_packet_num; }
        
        class packet_generator;
        friend class packet_generator;
        class packet_generator {
                // lock the copy constructor
                packet_generator(packet_generator &){}
                // store all possible types of packet
                static map<string,packet_generator*> prototypes;
            protected:
                // allow derived class to use it
                packet_generator() {}
                // after you create a new packet type, please register the factory of this payload type by this function
                void register_packet_type(packet_generator *h) { prototypes[h->type()] = h; }
                // you have to implement your own generate() to generate your payload
                virtual packet* generate ( packet *p = nullptr) = 0;
            public:
                // you have to implement your own type() to return your packet type
        	    virtual string type() = 0;
        	    // this function is used to generate any type of packet derived
        	    static packet * generate (string type) {
            		if(prototypes.find(type) != prototypes.end()){ // if this type derived exists 
            			return prototypes[type]->generate(); // generate it!!
            		}
            		std::cerr << "no such packet type" << std::endl; // otherwise
            		return nullptr;
            	}
            	static packet * replicate (packet *p) {
            	    if(prototypes.find(p->type()) != prototypes.end()){ // if this type derived exists 
            			return prototypes[p->type()]->generate(p); // generate it!!
            		}
            		std::cerr << "no such packet type" << std::endl; // otherwise
            		return nullptr;
            	}
            	static void print () {
            	    cout << "registered packet types: " << endl;
            	    for (map<string,packet::packet_generator*>::iterator it = prototypes.begin(); it != prototypes.end(); it ++)
            	        cout << it->second->type() << endl;
            	}
            	virtual ~packet_generator(){};
        };
};
map<string,packet::packet_generator*> packet::packet_generator::prototypes;
unsigned int packet::last_packet_id = 0 ;
int packet::live_packet_num = 0;


// this packet is used to tell the destination the msg
class SDN_data_packet: public packet {
        SDN_data_packet(SDN_data_packet &) {}
        
    protected:
        SDN_data_packet(){} // this constructor cannot be directly called by users
        SDN_data_packet(packet*p): packet(p->getHeader()->type(), p->getPayload()->type(), true, p->getPacketID()) {
            *(dynamic_cast<SDN_data_header*>(this->getHeader())) = *(dynamic_cast<SDN_data_header*> (p->getHeader()));
            *(dynamic_cast<SDN_data_payload*>(this->getPayload())) = *(dynamic_cast<SDN_data_payload*> (p->getPayload()));
            //DFS_path = (dynamic_cast<SDN_data_header*>(p))->DFS_path;
            //isVisited = (dynamic_cast<SDN_data_header*>(p))->isVisited;
        } // for duplicate
        SDN_data_packet(string _h, string _p): packet(_h,_p) {}
        
    public:
        virtual ~SDN_data_packet(){}
        string type() { return "SDN_data_packet"; }
        
        class SDN_data_packet_generator;
        friend class SDN_data_packet_generator;
        // SDN_data_packet is derived from packet_generator to generate a pub packet
        class SDN_data_packet_generator : public packet_generator{
                static SDN_data_packet_generator sample;
                // this constructor is only for sample to register this packet type
                SDN_data_packet_generator() { /*cout << "SDN_data_packet registered" << endl;*/ register_packet_type(&sample); }
            protected:
                virtual packet *generate (packet *p = nullptr){
                    // cout << "SDN_data_packet generated" << endl;
                    if ( nullptr == p )
                        return new SDN_data_packet("SDN_data_header","SDN_data_payload"); 
                    else
                        return new SDN_data_packet(p); // duplicate
                }
            public:
                virtual string type() { return "SDN_data_packet";}
                ~SDN_data_packet_generator(){}
        };
};
SDN_data_packet::SDN_data_packet_generator SDN_data_packet::SDN_data_packet_generator::sample;

class SDN_ctrl_packet: public packet {
        SDN_ctrl_packet(SDN_ctrl_packet &) {}
        
    protected:
        SDN_ctrl_packet(){} // this constructor cannot be directly called by users
        SDN_ctrl_packet(packet*p): packet(p->getHeader()->type(), p->getPayload()->type(), true, p->getPacketID()) {
            *(dynamic_cast<SDN_ctrl_header*>(this->getHeader())) = *(dynamic_cast<SDN_ctrl_header*> (p->getHeader()));
            *(dynamic_cast<SDN_ctrl_payload*>(this->getPayload())) = *(dynamic_cast<SDN_ctrl_payload*> (p->getPayload()));
            //DFS_path = (dynamic_cast<SDN_ctrl_header*>(p))->DFS_path;
            //isVisited = (dynamic_cast<SDN_ctrl_header*>(p))->isVisited;
        } // for duplicate
        SDN_ctrl_packet(string _h, string _p): packet(_h,_p) {}
        
    public:
        virtual ~SDN_ctrl_packet(){}
        string type() { return "SDN_ctrl_packet"; }
        
        class SDN_ctrl_packet_generator;
        friend class SDN_ctrl_packet_generator;
        // SDN_ctrl_packet is derived from packet_generator to generate a pub packet
        class SDN_ctrl_packet_generator : public packet_generator{
                static SDN_ctrl_packet_generator sample;
                // this constructor is only for sample to register this packet type
                SDN_ctrl_packet_generator() { /*cout << "SDN_ctrl_packet registered" << endl;*/ register_packet_type(&sample); }
            protected:
                virtual packet *generate (packet *p = nullptr){
                    // cout << "SDN_ctrl_packet generated" << endl;
                    if ( nullptr == p )
                        return new SDN_ctrl_packet("SDN_ctrl_header","SDN_ctrl_payload"); 
                    else
                        return new SDN_ctrl_packet(p); // duplicate
                }
            public:
                virtual string type() { return "SDN_ctrl_packet";}
                ~SDN_ctrl_packet_generator(){}
        };
};
SDN_ctrl_packet::SDN_ctrl_packet_generator SDN_ctrl_packet::SDN_ctrl_packet_generator::sample;

class node {
        // all nodes created in the program
        static map<unsigned int, node*> id_node_table;
        
        unsigned int id;
        map<unsigned int,bool> phy_neighbors;
        
    protected:
        node(node&){} // this constructor should not be used
        node(){} // this constructor should not be used
        node(unsigned int _id): id(_id) { id_node_table[_id] = this; }
    public:
        virtual ~node() { // erase the node
            id_node_table.erase (id) ;
        }
        virtual string type() = 0; // please define it in your derived node class
        
        void add_phy_neighbor (unsigned int _id, string link_type = "simple_link"); // we only add a directed link from id to _id
        void del_phy_neighbor (unsigned int _id); // we only delete a directed link from id to _id
        
        // you can use the function to get the node's neigbhors at this time
        // but in the project 3, you are not allowed to use this function 
        const map<unsigned int,bool> & getPhyNeighbors () { 
            return phy_neighbors;
        }
        
        
        void recv (packet *p) {
            packet *tp = p;
            recv_handler(tp); 
            packet::discard(p); 
        } // the packet will be directly deleted after the handler
        void send (packet *p);
        
        // receive the packet and do something; this is a pure virtual function
        virtual void recv_handler(packet *p) = 0;
        void send_handler(packet *P);
        
        static node * id_to_node (unsigned int _id) { return ((id_node_table.find(_id)!=id_node_table.end()) ? id_node_table[_id]: nullptr) ; }
        GET(getNodeID,unsigned int,id);
        
        static void del_node (unsigned int _id) {
            if (id_node_table.find(_id) != id_node_table.end())
                id_node_table.erase(_id);
        }
        static unsigned int getNodeNum () { return id_node_table.size(); }

        class node_generator {
                // lock the copy constructor
                node_generator(node_generator &){}
                // store all possible types of node
                static map<string,node_generator*> prototypes;
            protected:
                // allow derived class to use it
                node_generator() {}
                // after you create a new node type, please register the factory of this node type by this function
                void register_node_type(node_generator *h) { prototypes[h->type()] = h; }
                // you have to implement your own generate() to generate your node
                virtual node* generate(unsigned int _id) = 0;
            public:
                // you have to implement your own type() to return your node type
        	    virtual string type() = 0;
        	    // this function is used to generate any type of node derived
        	    static node * generate (string type, unsigned int _id) {
        	        if(id_node_table.find(_id)!=id_node_table.end()){
        	            std::cerr << "duplicate node id" << std::endl; // node id is duplicated
        	            return nullptr;
        	        }
        	        else if ( BROCAST_ID == _id ) {
        	            cerr << "BROCAST_ID cannot be used" << endl;
        	            return nullptr;
        	        }
            		else if(prototypes.find(type) != prototypes.end()){ // if this type derived exists 
            		    node * created_node = prototypes[type]->generate(_id);
            			return created_node; // generate it!!
            		}
            		std::cerr << "no such node type" << std::endl; // otherwise
            		return nullptr;
            	}
            	static void print () {
            	    cout << "registered node types: " << endl;
            	    for (map<string,node::node_generator*>::iterator it = prototypes.begin(); it != prototypes.end(); it ++)
            	        cout << it->second->type() << endl;
            	}
            	virtual ~node_generator(){};
        };
};
map<string,node::node_generator*> node::node_generator::prototypes;
map<unsigned int,node*> node::id_node_table;

class SDN_switch: public node {
        // map<unsigned int,bool> one_hop_neighbors; // you can use this variable to record the node's 1-hop neighbors
        map<unsigned int, unsigned int> table; // routing table on a single node

    protected:
        SDN_switch() {} // it should not be used
        SDN_switch(SDN_switch&) {} // it should not be used
        SDN_switch(unsigned int _id): node(_id) {} // this constructor cannot be directly called by users
    
    public:
        ~SDN_switch(){}
        string type() { return "SDN_switch"; }
        
        // please define recv_handler function to deal with the incoming packet
        virtual void recv_handler (packet *p);
        
        // void add_one_hop_neighbor (unsigned int n_id) { one_hop_neighbors[n_id] = true; }
        // unsigned int get_one_hop_neighbor_num () { return one_hop_neighbors.size(); }
        
        class SDN_switch_generator;
        friend class SDN_switch_generator;
        // SDN_switch is derived from node_generator to generate a node
        class SDN_switch_generator : public node_generator{
                static SDN_switch_generator sample;
                // this constructor is only for sample to register this node type
                SDN_switch_generator() { /*cout << "SDN_switch registered" << endl;*/ register_node_type(&sample); }
            protected:
                virtual node * generate(unsigned int _id){ /*cout << "SDN_switch generated" << endl;*/ return new SDN_switch(_id); }
            public:
                virtual string type() { return "SDN_switch";}
                ~SDN_switch_generator(){}
        };
};
SDN_switch::SDN_switch_generator SDN_switch::SDN_switch_generator::sample;

class mycomp {
    bool reverse;
    
    public:
        mycomp(const bool& revparam = false) { reverse=revparam ; }
        bool operator() (const event* lhs, const event* rhs) const;
};

class event {
        event(event*&){} // this constructor cannot be directly called by users
        static priority_queue < event*, vector < event* >, mycomp > events;
        static unsigned int cur_time; // timer
        static unsigned int end_time;
        
        // get the next event
        static event * get_next_event() ;
        static void add_event (event *e) { events.push(e); }
        static hash<string> event_seq;
        
    protected:
        unsigned int trigger_time;
        
        event(){} // it should not be used
        event(unsigned int _trigger_time): trigger_time(_trigger_time) {}

    public:
        virtual void trigger()=0;
        virtual ~event(){}

        virtual unsigned int event_priority() const = 0;
        unsigned int get_hash_value(string string_for_hash) const {
            unsigned int priority = event_seq (string_for_hash);
            return priority;
        }
        
        static void flush_events (); // only for debug
        
        GET(getTriggerTime,unsigned int,trigger_time);
        
        static void start_simulate( unsigned int _end_time ); // the function is used to start the simulation
        
        static unsigned int getCurTime() { return cur_time ; }
        static void getCurTime(unsigned int _cur_time) { cur_time = _cur_time; } 
        // static unsigned int getEndTime() { return end_time ; }
        // static void getEndTime(unsigned int _end_time) { end_time = _end_time; }
        
        virtual void print () const = 0; // the function is used to print the event information

        class event_generator{
                // lock the copy constructor
                event_generator(event_generator &){}
                // store all possible types of event
                static map<string,event_generator*> prototypes;
            protected:
                // allow derived class to use it
                event_generator() {}
                // after you create a new event type, please register the factory of this event type by this function
                void register_event_type(event_generator *h) { prototypes[h->type()] = h; }
                // you have to implement your own generate() to generate your event
                virtual event* generate(unsigned int _trigger_time, void * data) = 0;
            public:
                // you have to implement your own type() to return your event type
        	    virtual string type() = 0;
        	    // this function is used to generate any type of event derived
        	    static event * generate (string type, unsigned int _trigger_time, void * data) {
            		if(prototypes.find(type) != prototypes.end()){ // if this type derived exists
            		    event * e = prototypes[type]->generate(_trigger_time, data);
            		    add_event(e);
            		    return e; // generate it!!
            		}
            		std::cerr << "no such event type" << std::endl; // otherwise
            		return nullptr;
            	}
            	static void print () {
            	    cout << "registered event types: " << endl;
            	    for (map<string,event::event_generator*>::iterator it = prototypes.begin(); it != prototypes.end(); it ++)
            	        cout << it->second->type() << endl;
            	}
            	virtual ~event_generator(){}
        };
};
map<string,event::event_generator*> event::event_generator::prototypes;
priority_queue < event*, vector< event* >, mycomp > event::events;
hash<string> event::event_seq;

unsigned int event::cur_time = 0;
unsigned int event::end_time = 0;

void event::flush_events()
{ 
    cout << "**flush begin" << endl;
    while ( ! events.empty() ) {
        cout << setw(11) << events.top()->trigger_time << ": " << setw(11) << events.top()->event_priority() << endl;
        delete events.top();
        events.pop();
    }
    cout << "**flush end" << endl;
}
event * event::get_next_event() {
    if(events.empty()) 
        return nullptr; 
    event * e = events.top();
    events.pop(); 
    // cout << events.size() << " events remains" << endl;
    return e; 
}
void event::start_simulate(unsigned int _end_time) {
    if (_end_time<0) {
        cerr << "you should give a possitive value of _end_time" << endl;
        return;
    }
    end_time = _end_time;
    event *e; 
    e = event::get_next_event ();
    while ( e != nullptr && e->trigger_time <= end_time ) {
        if ( cur_time <= e->trigger_time )
            cur_time = e->trigger_time;
        else {
            cerr << "cur_time = " << cur_time << ", event trigger_time = " << e->trigger_time << endl;
            break;
        }

        // cout << "event trigger_time = " << e->trigger_time << endl;
        e->print(); // for log
        // cout << " event begin" << endl;
        e->trigger();
        // cout << " event end" << endl;
        delete e;
        e = event::get_next_event ();
    }
    // cout << "no more event" << endl;
}

bool mycomp::operator() (const event* lhs, const event* rhs) const {
    // cout << lhs->getTriggerTime() << ", " << rhs->getTriggerTime() << endl;
    // cout << lhs->type() << ", " << rhs->type() << endl;
    unsigned int lhs_pri = lhs->event_priority();
    unsigned int rhs_pri = rhs->event_priority();
    // cout << "lhs hash = " << lhs_pri << endl;
    // cout << "rhs hash = " << rhs_pri << endl;
    
    if (reverse) 
        return ((lhs->getTriggerTime()) == (rhs->getTriggerTime())) ? (lhs_pri < rhs_pri): ((lhs->getTriggerTime()) < (rhs->getTriggerTime()));
    else 
        return ((lhs->getTriggerTime()) == (rhs->getTriggerTime())) ? (lhs_pri > rhs_pri): ((lhs->getTriggerTime()) > (rhs->getTriggerTime()));
}

class recv_event: public event {
    public:
        class recv_data; // forward declaration
            
    private:
        recv_event(recv_event&) {} // this constructor cannot be used
        recv_event() {} // we don't allow users to new a recv_event by themselv
        unsigned int senderID; // the sender
        unsigned int receiverID; // the receiver; the packet will be given to the receiver
        packet *pkt; // the packet
        
    protected:
        // this constructor cannot be directly called by users; only by generator
        recv_event(unsigned int _trigger_time, void *data): event(_trigger_time), senderID(BROCAST_ID), receiverID(BROCAST_ID), pkt(nullptr){
            recv_data * data_ptr = (recv_data*) data;
            senderID = data_ptr->s_id;
            receiverID = data_ptr->r_id; // the packet will be given to the receiver
            pkt = data_ptr->_pkt;
        } 
        
    public:
        virtual ~recv_event(){}
        // recv_event will trigger the recv function
        virtual void trigger();
        
        unsigned int event_priority() const;
        
        class recv_event_generator;
        friend class recv_event_generator;
        // recv_event is derived from event_generator to generate a event
        class recv_event_generator : public event_generator{
                static recv_event_generator sample;
                // this constructor is only for sample to register this event type
                recv_event_generator() { /*cout << "recv_event registered" << endl;*/ register_event_type(&sample); }
            protected:
                virtual event * generate(unsigned int _trigger_time, void *data){ 
                    // cout << "recv_event generated" << endl; 
                    return new recv_event(_trigger_time, data); 
                }
                
            public:
                virtual string type() { return "recv_event";}
                ~recv_event_generator(){}
        };
        // this class is used to initialize the recv_event
        class recv_data{
            public:
                unsigned int s_id;
                unsigned int r_id;
                packet *_pkt;
        };
        
        void print () const;
};

recv_event::recv_event_generator recv_event::recv_event_generator::sample;

void recv_event::trigger() {
    if (pkt == nullptr) {
        cerr << "recv_event error: no pkt!" << endl; 
        return ; 
    }
    else if (node::id_to_node(receiverID) == nullptr){
        cerr << "recv_event error: no node " << receiverID << "!" << endl;
        delete pkt; return ;
    }
    node::id_to_node(receiverID)->recv(pkt); 
}
unsigned int recv_event::event_priority() const {
    string string_for_hash;
    string_for_hash = to_string(getTriggerTime()) + to_string(senderID) + to_string (receiverID) + to_string (pkt->getPacketID());
    return get_hash_value(string_for_hash);
}
// the recv_event::print() function is used for log file
void recv_event::print () const {
    cout << "time "          << setw(11) << event::getCurTime() 
         << "   recID"       << setw(11) << receiverID 
         << "   pktID"       << setw(11) << pkt->getPacketID()
         << "   srcID"       << setw(11) << pkt->getHeader()->getSrcID() 
         << "   dstID"       << setw(11) << pkt->getHeader()->getDstID() 
         << "   preID"       << setw(11) << pkt->getHeader()->getPreID()
         << "   nexID"       << setw(11) << pkt->getHeader()->getNexID()
         << "   "            << pkt->type()
         << endl;
    // cout << pkt->type()
    //      << "   time "       << setw(11) << event::getCurTime() 
    //      << "   recID "      << setw(11) << receiverID 
    //      << "   pktID"       << setw(11) << pkt->getPacketID()
    //      << "   srcID "      << setw(11) << pkt->getHeader()->getSrcID() 
    //      << "   dstID"       << setw(11) << pkt->getHeader()->getDstID() 
    //      << "   preID"       << setw(11) << pkt->getHeader()->getPreID()
    //      << "   nexID"       << setw(11) << pkt->getHeader()->getNexID()
    //      << endl;
}

class send_event: public event {
    public:
        class send_data; // forward declaration
            
    private:
        send_event (send_event &){}
        send_event (){} // we don't allow users to new a recv_event by themselves
        // this constructor cannot be directly called by users; only by generator
        unsigned int senderID; // the sender
        unsigned int receiverID; // the receiver 
        packet *pkt; // the packet
    
    protected:
        send_event (unsigned int _trigger_time, void *data): event(_trigger_time), senderID(BROCAST_ID), receiverID(BROCAST_ID), pkt(nullptr){
            send_data * data_ptr = (send_data*) data;
            senderID = data_ptr->s_id;
            receiverID = data_ptr->r_id;
            pkt = data_ptr->_pkt;
        } 
        
    public:
        virtual ~send_event(){}
        // send_event will trigger the send function
        virtual void trigger();
        
        unsigned int event_priority() const;
        
        class send_event_generator;
        friend class send_event_generator;
        // send_event is derived from event_generator to generate a event
        class send_event_generator : public event_generator{
                static send_event_generator sample;
                // this constructor is only for sample to register this event type
                send_event_generator() { /*cout << "send_event registered" << endl;*/ register_event_type(&sample); }
            protected:
                virtual event * generate(unsigned int _trigger_time, void *data){ 
                    // cout << "send_event generated" << endl; 
                    return new send_event(_trigger_time, data); 
                }
            
            public:
                virtual string type() { return "send_event";}
                ~send_event_generator(){}
        };
        // this class is used to initialize the send_event
        class send_data{
            public:
                unsigned int s_id;
                unsigned int r_id;
                packet *_pkt;
                unsigned int t;
        };
        
        void print () const;
};
send_event::send_event_generator send_event::send_event_generator::sample;

void send_event::trigger() {
    if (pkt == nullptr) {
        cerr << "send_event error: no pkt!" << endl; 
        return ; 
    }
    else if (node::id_to_node(senderID) == nullptr){
        cerr << "send_event error: no node " << senderID << "!" << endl;
        delete pkt; return ;
    }
    node::id_to_node(senderID)->send(pkt);
}
unsigned int send_event::event_priority() const {
    string string_for_hash;
    string_for_hash = to_string(getTriggerTime()) + to_string(senderID) + to_string (receiverID) + to_string (pkt->getPacketID());
    return get_hash_value(string_for_hash);
}
// the send_event::print() function is used for log file
void send_event::print () const {
    cout << "time "          << setw(11) << event::getCurTime() 
         << "   senID"       << setw(11) << senderID 
         << "   pktID"       << setw(11) << pkt->getPacketID()
         << "   srcID"       << setw(11) << pkt->getHeader()->getSrcID() 
         << "   dstID"       << setw(11) << pkt->getHeader()->getDstID() 
         << "   preID"       << setw(11) << pkt->getHeader()->getPreID()
         << "   nexID"       << setw(11) << pkt->getHeader()->getNexID()
         << "   "            << pkt->type()
         //<< "   msg"         << setw(11) << dynamic_cast<SDN_data_payload*>(pkt->getPayload())->getMsg()
         << endl;
    // cout << pkt->type()
    //      << "   time "       << setw(11) << event::getCurTime() 
    //      << "   senID "      << setw(11) << senderID
    //      << "   pktID"       << setw(11) << pkt->getPacketID()
    //      << "   srcID "      << setw(11) << pkt->getHeader()->getSrcID() 
    //      << "   dstID"       << setw(11) << pkt->getHeader()->getDstID() 
    //      << "   preID"       << setw(11) << pkt->getHeader()->getPreID()
    //      << "   nexID"       << setw(11) << pkt->getHeader()->getNexID()
    //      << endl;
}

////////////////////////////////////////////////////////////////////////////////

class SDN_data_pkt_gen_event: public event {
    public:
        class gen_data; // forward declaration
            
    private:
        SDN_data_pkt_gen_event (SDN_data_pkt_gen_event &){}
        SDN_data_pkt_gen_event (){} // we don't allow users to new a recv_event by themselves
        // this constructor cannot be directly called by users; only by generator
        unsigned int src; // the src
        unsigned int dst; // the dst 
        // packet *pkt; // the packet
        string msg;
    
    protected:
        SDN_data_pkt_gen_event (unsigned int _trigger_time, void *data): event(_trigger_time), src(BROCAST_ID), dst(BROCAST_ID){
            pkt_gen_data * data_ptr = (pkt_gen_data*) data;
            src = data_ptr->src_id;
            dst = data_ptr->dst_id;
            // pkt = data_ptr->_pkt;
            msg = data_ptr->msg;
        } 
        
    public:
        virtual ~SDN_data_pkt_gen_event(){}
        // SDN_data_pkt_gen_event will trigger the packet gen function
        virtual void trigger();
        
        unsigned int event_priority() const;
        
        class SDN_data_pkt_gen_event_generator;
        friend class SDN_data_pkt_gen_event_generator;
        // SDN_data_pkt_gen_event_generator is derived from event_generator to generate an event
        class SDN_data_pkt_gen_event_generator : public event_generator{
                static SDN_data_pkt_gen_event_generator sample;
                // this constructor is only for sample to register this event type
                SDN_data_pkt_gen_event_generator() { /*cout << "send_event registered" << endl;*/ register_event_type(&sample); }
            protected:
                virtual event * generate(unsigned int _trigger_time, void *data){ 
                    // cout << "send_event generated" << endl; 
                    return new SDN_data_pkt_gen_event(_trigger_time, data); 
                }
            
            public:
                virtual string type() { return "SDN_data_pkt_gen_event";}
                ~SDN_data_pkt_gen_event_generator(){}
        };
        // this class is used to initialize the SDN_data_pkt_gen_event
        class pkt_gen_data{
            public:
                unsigned int src_id;
                unsigned int dst_id;
                string msg;
                // packet *_pkt;
        };
        
        void print () const;
};
SDN_data_pkt_gen_event::SDN_data_pkt_gen_event_generator SDN_data_pkt_gen_event::SDN_data_pkt_gen_event_generator::sample;

void SDN_data_pkt_gen_event::trigger() {
    if (node::id_to_node(src) == nullptr){
        cerr << "SDN_data_pkt_gen_event error: no node " << src << "!" << endl;
        return ;
    }
    else if ( dst != BROCAST_ID && node::id_to_node(dst) == nullptr ) {
        cerr << "SDN_data_pkt_gen_event error: no node " << dst << "!" << endl;
        return;
    }
    
    SDN_data_packet *pkt = dynamic_cast<SDN_data_packet*> ( packet::packet_generator::generate("SDN_data_packet") );
    if (pkt == nullptr) { 
        cerr << "packet type is incorrect" << endl; return; 
    }
    SDN_data_header *hdr = dynamic_cast<SDN_data_header*> ( pkt->getHeader() );
    SDN_data_payload *pld = dynamic_cast<SDN_data_payload*> ( pkt->getPayload() );
    
    if (hdr == nullptr) {
        cerr << "header type is incorrect" << endl; return ;
    }
    if (pld == nullptr) {
        cerr << "payload type is incorrect" << endl; return ;
    }

    hdr->setSrcID(src);
    hdr->setDstID(dst);
    hdr->setPreID(src); // this column is not important when the packet is first received by the src (i.e., just generated)
    hdr->setNexID(src); // this column is not important when the packet is first received by the src (i.e., just generated)

    pld->setMsg(msg);
    
    recv_event::recv_data e_data;
    e_data.s_id = src;
    e_data.r_id = src; // to make the packet start from the src
    e_data._pkt = pkt;
    
    recv_event *e = dynamic_cast<recv_event*> ( event::event_generator::generate("recv_event", trigger_time, (void *)&e_data) );

}
unsigned int SDN_data_pkt_gen_event::event_priority() const {
    string string_for_hash;
    string_for_hash = to_string(getTriggerTime()) + to_string(src) + to_string (dst) ; //to_string (pkt->getPacketID());
    return get_hash_value(string_for_hash);
}
// the SDN_data_pkt_gen_event::print() function is used for log file
void SDN_data_pkt_gen_event::print () const {
    cout << "time "          << setw(11) << event::getCurTime() 
         << "        "       << setw(11) << " "
         << "        "       << setw(11) << " "
         << "   srcID"       << setw(11) << src
         << "   dstID"       << setw(11) << dst
         << "        "       << setw(11) << " "
         << "        "       << setw(11) << " "
         << "   SDN_data_packet generating"
         << endl;
}

class SDN_ctrl_pkt_gen_event: public event {
    public:
        class gen_data; // forward declaration
            
    private:
        SDN_ctrl_pkt_gen_event (SDN_ctrl_pkt_gen_event &){}
        SDN_ctrl_pkt_gen_event (){} // we don't allow users to new a recv_event by themselves
        // this constructor cannot be directly called by users; only by generator
        unsigned int src; // the src
        unsigned int dst; // the dst 
        unsigned int mat;
        unsigned int act;
        // packet *pkt; // the packet
        string msg;
    
    protected:
        SDN_ctrl_pkt_gen_event (unsigned int _trigger_time, void *data): event(_trigger_time), src(BROCAST_ID), dst(BROCAST_ID){
            pkt_gen_data * data_ptr = (pkt_gen_data*) data;
            src = data_ptr->src_id;
            dst = data_ptr->dst_id;
            // pkt = data_ptr->_pkt;
            mat = data_ptr->mat_id;
            act = data_ptr->act_id;
            msg = data_ptr->msg;
        } 
        
    public:
        virtual ~SDN_ctrl_pkt_gen_event(){}
        // SDN_ctrl_pkt_gen_event will trigger the packet gen function
        virtual void trigger();
        
        unsigned int event_priority() const;
        
        class SDN_ctrl_pkt_gen_event_generator;
        friend class SDN_ctrl_pkt_gen_event_generator;
        // SDN_ctrl_pkt_gen_event_generator is derived from event_generator to generate an event
        class SDN_ctrl_pkt_gen_event_generator : public event_generator{
                static SDN_ctrl_pkt_gen_event_generator sample;
                // this constructor is only for sample to register this event type
                SDN_ctrl_pkt_gen_event_generator() { /*cout << "send_event registered" << endl;*/ register_event_type(&sample); }
            protected:
                virtual event * generate(unsigned int _trigger_time, void *data){ 
                    // cout << "send_event generated" << endl; 
                    return new SDN_ctrl_pkt_gen_event(_trigger_time, data); 
                }
            
            public:
                virtual string type() { return "SDN_ctrl_pkt_gen_event";}
                ~SDN_ctrl_pkt_gen_event_generator(){}
        };
        // this class is used to initialize the SDN_ctrl_pkt_gen_event
        class pkt_gen_data{
            public:
                unsigned int src_id; // the controller
                unsigned int dst_id; // the node that should update its rule
                unsigned int mat_id; // the target of the rule
                unsigned int act_id; // the next hop toward the target recorded in the rule
                string msg;
                // packet *_pkt;
        };
        
        void print () const;
};
SDN_ctrl_pkt_gen_event::SDN_ctrl_pkt_gen_event_generator SDN_ctrl_pkt_gen_event::SDN_ctrl_pkt_gen_event_generator::sample;

void SDN_ctrl_pkt_gen_event::trigger() {
    if ( dst == BROCAST_ID || node::id_to_node(dst) == nullptr ) {
        cerr << "SDN_ctrl_pkt_gen_event error: no node " << dst << "!" << endl;
        return;
    }
    
    SDN_ctrl_packet *pkt = dynamic_cast<SDN_ctrl_packet*> ( packet::packet_generator::generate("SDN_ctrl_packet") );
    if (pkt == nullptr) { 
        cerr << "packet type is incorrect" << endl; return; 
    }
    SDN_ctrl_header *hdr = dynamic_cast<SDN_ctrl_header*> ( pkt->getHeader() );
    SDN_ctrl_payload *pld = dynamic_cast<SDN_ctrl_payload*> ( pkt->getPayload() );
    
    if (hdr == nullptr) {
        cerr << "header type is incorrect" << endl; return ;
    }
    if (pld == nullptr) {
        cerr << "payload type is incorrect" << endl; return ;
    }

    /******************************************************
     * change dst to src to send packet to the controller *
     ******************************************************/
    hdr->setSrcID(src); 
    hdr->setDstID(dst);
    hdr->setPreID(src);
    hdr->setNexID(src); // in hw3, you should set NexID to src
    // payload
    pld->setMsg(msg);
    pld->setMatID(mat);
    pld->setActID(act);
    
    recv_event::recv_data e_data;
    e_data.s_id = src;
    e_data.r_id = src; // in hw3, you should set r_id it src
    e_data._pkt = pkt;
    
    recv_event *e = dynamic_cast<recv_event*> ( event::event_generator::generate("recv_event",trigger_time, (void *)&e_data) );
}
unsigned int SDN_ctrl_pkt_gen_event::event_priority() const {
    string string_for_hash;
    string_for_hash = to_string(getTriggerTime()) + to_string(src) + to_string(dst) + to_string(mat) + to_string(act); //to_string (pkt->getPacketID());
    return get_hash_value(string_for_hash);
}
// the SDN_ctrl_pkt_gen_event::print() function is used for log file
void SDN_ctrl_pkt_gen_event::print () const {
    cout << "time "          << setw(11) << event::getCurTime() 
         << "        "       << setw(11) << " "
         << "        "       << setw(11) << " "
         << "   srcID"       << setw(11) << src 
         << "   dstID"       << setw(11) << dst
         << "   matID"       << setw(11) << mat
         << "   actID"       << setw(11) << act
         << "   SDN_ctrl_packet generating"
         << endl;
}

////////////////////////////////////////////////////////////////////////////////

class link {
        // all links created in the program
        static map< pair<unsigned int,unsigned int>, link*> id_id_link_table;
        
        unsigned int id1; // from
        unsigned int id2; // to
        
    protected:
        link(link&){} // this constructor should not be used
        link(){} // this constructor should not be used
        link(unsigned int _id1, unsigned int _id2): id1(_id1), id2(_id2) { id_id_link_table[pair<unsigned int,unsigned int>(id1,id2)] = this; }

    public:
        virtual ~link() { 
            id_id_link_table.erase (pair<unsigned int,unsigned int>(id1,id2)); // erase the link
        }
        
        static link * id_id_to_link (unsigned int _id1, unsigned int _id2) { 
            return ((id_id_link_table.find(pair<unsigned int,unsigned int>(_id1,_id2))!=id_id_link_table.end()) ? id_id_link_table[pair<unsigned,unsigned>(_id1,_id2)]: nullptr) ; 
        }

        virtual double getLatency() = 0; // you must implement your own latency
        
        static void del_link (unsigned int _id1, unsigned int _id2) {
            pair<unsigned int, unsigned int> temp;
            if (id_id_link_table.find(temp)!=id_id_link_table.end())
                id_id_link_table.erase(temp); 
        }

        static unsigned int getLinkNum () { return id_id_link_table.size(); }

        class link_generator {
                // lock the copy constructor
                link_generator(link_generator &){}
                // store all possible types of link
                static map<string,link_generator*> prototypes;
            protected:
                // allow derived class to use it
                link_generator() {}
                // after you create a new link type, please register the factory of this link type by this function
                void register_link_type(link_generator *h) { prototypes[h->type()] = h; }
                // you have to implement your own generate() to generate your link
                virtual link* generate(unsigned int _id1, unsigned int _id2) = 0;
            public:
                // you have to implement your own type() to return your link type
        	    virtual string type() = 0;
        	    // this function is used to generate any type of link derived
        	    static link * generate (string type, unsigned int _id1, unsigned int _id2) {
        	        if(id_id_link_table.find(pair<unsigned int,unsigned int>(_id1,_id2))!=id_id_link_table.end()){
        	            std::cerr << "duplicate link id" << std::endl; // link id is duplicated
        	            return nullptr;
        	        }
        	        else if ( BROCAST_ID == _id1 || BROCAST_ID == _id2 ) {
        	            cerr << "BROCAST_ID cannot be used" << endl;
        	            return nullptr;
        	        }
            		else if (prototypes.find(type) != prototypes.end()){ // if this type derived exists 
            		    link * created_link = prototypes[type]->generate(_id1,_id2);
            			return created_link; // generate it!!
            		}
            		std::cerr << "no such link type" << std::endl; // otherwise
            		return nullptr;
            	}
            	static void print () {
            	    cout << "registered link types: " << endl;
            	    for (map<string,link::link_generator*>::iterator it = prototypes.begin(); it != prototypes.end(); it ++)
            	        cout << it->second->type() << endl;
            	}
            	virtual ~link_generator(){};
        };
};
map<string,link::link_generator*> link::link_generator::prototypes;
map<pair<unsigned int,unsigned int>, link*> link::id_id_link_table;

void node::add_phy_neighbor (unsigned int _id, string link_type){
    if (id == _id) return; // if the two nodes are the same...
    if (id_node_table.find(_id)==id_node_table.end()) return; // if this node does not exist
    if (phy_neighbors.find(_id)!=phy_neighbors.end()) return; // if this neighbor has been added
    phy_neighbors[_id] = true;
    
    link::link_generator::generate(link_type,id,_id);
}
void node::del_phy_neighbor (unsigned int _id){
    phy_neighbors.erase(_id);
    
}


class simple_link: public link {
    protected:
        simple_link() {} // it should not be used outside the class
        simple_link(simple_link&) {} // it should not be used
        simple_link(unsigned int _id1, unsigned int _id2): link (_id1,_id2){} // this constructor cannot be directly called by users
    
    public:
        virtual ~simple_link() {}
        virtual double getLatency() { return ONE_HOP_DELAY; } // you can implement your own latency
        
        class simple_link_generator;
        friend class simple_link_generator;
        // simple_link is derived from link_generator to generate a link
        class simple_link_generator : public link_generator {
                static simple_link_generator sample;
                // this constructor is only for sample to register this link type
                simple_link_generator() { /*cout << "simple_link registered" << endl;*/ register_link_type(&sample); }
            protected:
                virtual link * generate(unsigned int _id1, unsigned int _id2) 
                { /*cout << "simple_link generated" << endl;*/ return new simple_link(_id1,_id2); }
            public:
                virtual string type() { return "simple_link"; }
                ~simple_link_generator(){}
        };
};

simple_link::simple_link_generator simple_link::simple_link_generator::sample;


// the data_packet_event function is used to add an initial event
void data_packet_event (unsigned int src, unsigned int dst, unsigned int t = 0, string msg = "default"){
    if ( node::id_to_node(src) == nullptr || (dst != BROCAST_ID && node::id_to_node(dst) == nullptr) ) {
        cerr << "src or dst is incorrect" << endl; return ;
        return;
    }

    SDN_data_pkt_gen_event::pkt_gen_data e_data;
    e_data.src_id = src;
    e_data.dst_id = dst;
    e_data.msg = msg;
    
    // recv_event *e = dynamic_cast<recv_event*> ( event::event_generator::generate("recv_event",t, (void *)&e_data) );
    SDN_data_pkt_gen_event *e = dynamic_cast<SDN_data_pkt_gen_event*> ( event::event_generator::generate("SDN_data_pkt_gen_event",t, (void *)&e_data) );
    if (e == nullptr) cerr << "event type is incorrect" << endl;
}

// the ctrl_packet_event function is used to add an initial event
void ctrl_packet_event (unsigned int con_id, unsigned int id, unsigned int mat, unsigned int act, unsigned int t = event::getCurTime(), string msg = "default"){
// void ctrl_packet_event (unsigned int dst, unsigned int t = 0, string msg = "default"){
    if ( id == BROCAST_ID || node::id_to_node(id) == nullptr ) {
        cerr << "id is incorrect" << endl; return;
    }
    
    unsigned int src = con_id;
    SDN_ctrl_pkt_gen_event::pkt_gen_data e_data;
    e_data.src_id = src;
    e_data.dst_id = id;
    e_data.mat_id = mat;
    e_data.act_id = act;
    e_data.msg = msg;
    
    SDN_ctrl_pkt_gen_event *e = dynamic_cast<SDN_ctrl_pkt_gen_event*> ( event::event_generator::generate("SDN_ctrl_pkt_gen_event",t, (void *)&e_data) );
    if (e == nullptr) cerr << "event type is incorrect" << endl;
}

// send_handler function is used to transmit packet p based on the information in the header
// Note that the packet p will not be discard after send_handler ()

void node::send_handler(packet *p){
    packet *_p = packet::packet_generator::replicate(p);
    send_event::send_data e_data;
    e_data.s_id = _p->getHeader()->getPreID();
    e_data.r_id = _p->getHeader()->getNexID();
    e_data._pkt = _p;
    send_event *e = dynamic_cast<send_event*> (event::event_generator::generate("send_event",event::getCurTime(), (void *)&e_data) );
    if (e == nullptr) cerr << "event type is incorrect" << endl;
}

void node::send(packet *p){ // this function is called by event; not for the user
    if (p == nullptr) return;
    
    unsigned int _nexID = p->getHeader()->getNexID();
    for ( map<unsigned int,bool>::iterator it = phy_neighbors.begin(); it != phy_neighbors.end(); it ++) {
        unsigned int nb_id = it->first; // neighbor id
        
        if (nb_id != _nexID && BROCAST_ID != _nexID) continue; // this neighbor will not receive the packet
        
        unsigned int trigger_time = event::getCurTime() + link::id_id_to_link(id, nb_id)->getLatency() ; // we simply assume that the delay is fixed
        // cout << "node " << id << " send to node " <<  nb_id << endl;
        recv_event::recv_data e_data;
        e_data.s_id = id;    // set the sender   (i.e., preID)
        e_data.r_id = nb_id; // set the receiver (i.e., nexID)
        
        packet *p2 = packet::packet_generator::replicate(p);
        e_data._pkt = p2;
        
        recv_event *e = dynamic_cast<recv_event*> (event::event_generator::generate("recv_event", trigger_time, (void*) &e_data)); // send the packet to the neighbor
        if (e == nullptr) cerr << "event type is incorrect" << endl;
    }
    packet::discard(p);
}

/*****************************************************
 * the implementation of reecv_handler in SDN_switch *
 *****************************************************/

void SDN_switch::recv_handler (packet *p){
    if (p == nullptr)
        return;
    
    if (p->type() == "SDN_data_packet") {
        // convert the packet type to data packet
        SDN_data_packet * p2 = dynamic_cast<SDN_data_packet*> (p);

        // if the node which received this packet is the destination that packet was sent to
        if(getNodeID() == p2->getHeader()->getDstID())
            return;

        // if the node can't find a proper node to send from the table (the switch hasn't been installed)
        if(table.find(p2->getHeader()->getDstID()) == table.end())
            return;
        
        // otherwise, modify the info in packet and forward it to next node
        p2->getHeader()->setPreID ( getNodeID() );
        p2->getHeader()->setNexID ( table[p->getHeader()->getDstID()] );
        send_handler (p2);
    } else if (p->type() == "SDN_ctrl_packet") {

        // convert the types of packet and payload to the right ones
        SDN_ctrl_packet *p3 = nullptr;
        p3 = dynamic_cast<SDN_ctrl_packet*> (p);
        SDN_ctrl_payload *l3 = nullptr;
        l3 = dynamic_cast<SDN_ctrl_payload*> (p3->getPayload());
        
        // modify the table in this switch
        unsigned mat = l3->getMatID();
        unsigned act = l3->getActID();
        table[mat] = act;
        
        /*******************************************************************
         * change dst, pre, and next to send packet back to the controller *
         *******************************************************************/
        unsigned int pre_id = p3->getHeader()->getPreID();
        p3->getHeader()->setDstID ( pre_id );
        p3->getHeader()->setPreID ( getNodeID() );
        p3->getHeader()->setNexID ( pre_id);
        send_handler (p3);
    }
}

/****************************************
 * the implementation of SDN_controller *
 ****************************************/

class SDN_controller: public node {
    protected:
        SDN_controller() {} // it should not be used
        SDN_controller(SDN_controller&) {} // it should not be used
        SDN_controller(unsigned int _id): node(_id) {}
    public:
        ~SDN_controller(){}
        string type() { return "SDN_controller"; }
        
        virtual void recv_handler (packet *p);

        /***********************************************
         * member and member function that used in hw3 *
         ***********************************************/
        const unsigned int switch_num = node::getNodeNum() - 1; // # of nodes = # of switch + # of controller
        const unsigned int con_id = switch_num;
        bool isInitialized = false; // simple flag to check if the vector are initialized
        vector<unsigned int> stat_of_node; // current state of nodes, 0: initial, 1:already installed, 2: already updated
        vector<unsigned int> nodes_to_update; // the nodes to update in each turn
        vector<unsigned int> getUpdateNodes(vector<unsigned int> &next_nodes, unsigned int ignore); // get the nodes that needed to be updated in each round
        bool isUpdateEnd(unsigned int ignore); // check if all the updates on nodes are done
        
        // a node to store the new routing table of a single switch
        class Node {
            public:
                map<unsigned int, unsigned int> new_table;
                Node() {};
                ~Node() {};
        };
        vector<Node> node_list;
        
        class SDN_controller_generator;
        friend class SDN_controller_generator;
        // SDN_controller is derived from node_generator to generate a node
        class SDN_controller_generator : public node_generator{
                static SDN_controller_generator sample;
                // this constructor is only for sample to register this node type
                SDN_controller_generator() { /*cout << "SDN_controller registered" << endl;*/ register_node_type(&sample); }
            protected:
                virtual node * generate(unsigned int _id){ /*cout << "SDN_controller generated" << endl;*/ return new SDN_controller(_id); }
            public:
                virtual string type() { return "SDN_controller";}
                ~SDN_controller_generator(){}
        };
};
SDN_controller::SDN_controller_generator SDN_controller::SDN_controller_generator::sample;

/*********************************************************
 * the implementation of recv_handler in SDN_controller *
 *********************************************************/

void SDN_controller::recv_handler (packet *p) {
    if(p == nullptr)
        return;

    // casting and get value of fields: "match" and "action"
    SDN_ctrl_packet * p2 = nullptr;
    p2 = dynamic_cast<SDN_ctrl_packet*> (p);
    SDN_ctrl_payload *l2 = nullptr;
    l2 = dynamic_cast<SDN_ctrl_payload*> (p2->getPayload());
    unsigned mat = l2->getMatID();
    unsigned act = l2->getActID();

    // resize the vector when access for the first time
    if(!isInitialized) {
        stat_of_node.resize(switch_num, 0);
        node_list.resize(switch_num);
        isInitialized = true;
    }

    // the destination of packet is controller! (sended back from switches)
    if(p->type() == "SDN_ctrl_packet" && p->getHeader()->getDstID() == getNodeID()) {
        // if the controller is still dealing with install packet
        if(nodes_to_update.empty())
            return;
        
        // if the packet is sended back by switches, record it in vector: nodes
        stat_of_node.at(p2->getHeader()->getPreID()) = 2;

        // if there is any switches who hasn't sended back the packet
        for(unsigned int i = 0; i < stat_of_node.size(); i++) {
            if(stat_of_node.at(i) == 1)
                return;
        }

        // handle the update in each round
        if(!isUpdateEnd(mat)) {
            nodes_to_update = getUpdateNodes(nodes_to_update, mat);
            for(unsigned int i = 0; i < nodes_to_update.size(); i++) {
                int act = node_list.at(nodes_to_update.at(i)).new_table[mat];
                ctrl_packet_event(con_id, nodes_to_update.at(i), mat, act);
                stat_of_node.at(nodes_to_update.at(i)) = 1;
            }
        }
    } else if(p->type() == "SDN_ctrl_packet" && p->getHeader()->getDstID() != getNodeID()) {
        // not forward, but create a new event!
        if("install" == l2->getMsg()) {
            ctrl_packet_event(con_id, p2->getHeader()->getDstID(), mat, act);
        } else if("update" == l2->getMsg()) {
            unsigned int node_id = p2->getHeader()->getDstID();
            node_list.at(node_id).new_table[mat] = act;

            if(mat == act) {
                int act = node_list.at(p2->getHeader()->getDstID()).new_table[mat];
                ctrl_packet_event(con_id, p2->getHeader()->getDstID(), mat, act);
                nodes_to_update.push_back(p2->getHeader()->getDstID());
                stat_of_node.at(p2->getHeader()->getDstID()) = 1;
            }
        } else { // the packet is neither install nor update packet
            // forward the packet
            p2->getHeader()->setPreID ( getNodeID() ); // the previous node is itself
            p2->getHeader()->setNexID ( p->getHeader()->getDstID() ); // the next node id is the node to send to, not the controller
            send_handler (p2);
        }
    }
}

vector<unsigned int> SDN_controller::getUpdateNodes(vector<unsigned int> &next_nodes, unsigned int ignore) {
    vector<unsigned int> tmp;

    for(unsigned int i = 0; i < stat_of_node.size(); i++) {
        for(unsigned int j = 0; j < next_nodes.size(); j++) {
            for(auto itr : node_list.at(i).new_table) {
                if(i != ignore && itr.first == ignore && itr.second == next_nodes.at(j))
                    tmp.push_back(i);
            }
        }
    }
    return tmp;
};

bool SDN_controller::isUpdateEnd(unsigned int ignore) {
    for(unsigned int i = 0; i < stat_of_node.size(); i++) {
        // 1 represent the node has been updated
        if(ignore != i && 2 != stat_of_node.at(i))
            return false;
    }
    return true;
};

// constant for dijkstra algorithm
const unsigned int MAX = 4096;

/****************************************************************************
 * the handler that read the data and preprocess them before the simulation *
 ****************************************************************************/

class Data_handler {
    // forward declaration
    private:
        class Node;

    public:
        void startSetup(); // set things up and get ready to start the simulation
        void SetSize(); // set the vector of destinations and adjacency matrix to apprpriate size
        void generateNode(); // instantiate controllers and switches
        void buildTable(); // build the old and new routing table
        void Dijkstra(vector<Node> &node_list, unsigned int dst, bool is_old = true); // shortest path algorithm
        unsigned int getMin(vector<unsigned long> distance_arr, vector<bool> is_found); // function derived from Dijkstra()
        void setDataEvent(); // create the data packet event in the beginning
        void setCtrlEvent(); // create the ctrl packet event in the beginning
        unsigned int get_dur_time() { return dur_time; }; // accesssor
        Data_handler() {};
        ~Data_handler() {};

    private:
        unsigned int node_num, dst_num, link_num;
        unsigned int inst_time, updt_time, dur_time;
        vector<unsigned int> dest_list; // store the destination point
        unsigned int link_id, node1, node2, old_weight, new_weight;

        // single node in routing table
        class Node {
            public:
                vector<unsigned int> old_weight_list, new_weight_list; 
                map<unsigned int, unsigned int> old_table, new_table;
                Node() {};
                ~Node() {};
        };
        vector<Node> node_list;

        // an object for reading information about data event
        class Event {
            public: 
                unsigned int time;
                unsigned int src_id;
                unsigned int dst_id;
                unsigned int node_id;
                Event() {};
                ~Event() {};
        };
        Event event;
};

void Data_handler::generateNode() {
    // generate switch nodes
    for (unsigned int id = 0; id < node_num; id++)
        node::node_generator::generate("SDN_switch",id);

    // create the controller node
    unsigned int con_id = node::getNodeNum(); // id of controller is the number of SDN_switch nodes
    node::node_generator::generate("SDN_controller", con_id);

    // link all the switches to the controller
    for(unsigned int i = 0; i < con_id; i++) {
        node::id_to_node(con_id)->add_phy_neighbor(i);
        node::id_to_node(i)->add_phy_neighbor(con_id);
    }

}

void Data_handler::SetSize() {
    dest_list.resize(dst_num);

    node_list.resize(node_num);
    for(auto &i : node_list) {
        i.old_weight_list.resize(node_num, MAX); // MAX: 4096
        i.new_weight_list.resize(node_num, MAX);
    }
}

void Data_handler::startSetup() {
    // read number of node, dst, link and the network update time
    cin >> node_num >> dst_num >> link_num;
    cin >> inst_time >> updt_time >> dur_time;

    SetSize();
    generateNode();
    
    // read the destination points
    for(unsigned int i = 0; i < dst_num; i++)
        cin >> dest_list.at(i);

    // read the data and create a adjacency matrix
    for(unsigned int i = 0; i < link_num; i++) {
        cin >> link_id >> node1 >> node2 >> old_weight >> new_weight;
        node_list.at(node1).old_weight_list.at(node2) = old_weight;
        node_list.at(node2).old_weight_list.at(node1) = old_weight;
        node_list.at(node1).new_weight_list.at(node2) = new_weight;
        node_list.at(node2).new_weight_list.at(node1) = new_weight;

        // add neighbor relations for packet transfer
        node::id_to_node(node1)->add_phy_neighbor(node2);
        node::id_to_node(node2)->add_phy_neighbor(node1);
    }

    setDataEvent();
    buildTable();
    setCtrlEvent();
}

void Data_handler::buildTable() {
    for(auto i : dest_list) {
        Dijkstra(node_list, i);
        Dijkstra(node_list, i, false);
    }
}

void Data_handler::Dijkstra(vector<Node> &node_list, unsigned int dst, bool is_old)
{   
    vector<unsigned long> distance_arr; // store the distance between the start point and other nodes
    vector<bool> is_found; // record the state of each node

    // initialize
    distance_arr.resize(node_num, MAX);
    distance_arr.at(dst) = 0;
    is_found.resize(node_num, false);

    // use this code snippet to let each table of node hold same number of entries
    if(is_old)
        node_list.at(dst).old_table[dst] = dst; // the next node of the destination is the destination itself
    else
        node_list.at(dst).new_table[dst] = dst;
    
    for(unsigned int i = 0; i < node_num - 1; i++) {
        unsigned int min_point = getMin(distance_arr, is_found); // get the smallest node that have the shortest distance between root node
        is_found.at(min_point) = true;

        // update all distance between neighbor nodes and current point
        for(unsigned int j = 0; j < node_num; j++) {
            if(is_found.at(j))
                continue;
            if(is_old) {
                if(distance_arr.at(min_point) + node_list.at(min_point).old_weight_list.at(j) == distance_arr.at(j)) {
                    if(min_point < node_list.at(j).old_table[dst]) {
                        node_list.at(j).old_table[dst] = min_point;
                    }
                }
                if(distance_arr.at(min_point) + node_list.at(min_point).old_weight_list.at(j) < distance_arr.at(j)) {
                    distance_arr.at(j) = distance_arr.at(min_point) + node_list.at(min_point).old_weight_list.at(j);
                    node_list.at(j).old_table[dst] = min_point;
                }
            } else {
                if(distance_arr.at(min_point) + node_list.at(min_point).new_weight_list.at(j) == distance_arr.at(j)) {
                    if(min_point < node_list.at(j).new_table[dst]) {
                        node_list.at(j).new_table[dst] = min_point;
                    }
                }
                if(distance_arr.at(min_point) + node_list.at(min_point).new_weight_list.at(j) < distance_arr.at(j)) {
                    distance_arr.at(j) = distance_arr.at(min_point) + node_list.at(min_point).new_weight_list.at(j);
                    node_list.at(j).new_table[dst] = min_point;
                }
            }
        }
    }
}

unsigned int Data_handler::getMin(vector<unsigned long> distance_arr, vector<bool> is_found)
{
    unsigned int minPos = 0;
    unsigned long min = MAX;

    for(unsigned int i = 0; i < node_num; i++) {
        if(distance_arr.at(i) < min && !is_found.at(i)) {
            min = distance_arr.at(i);
            minPos = i;
        }
    }
    return minPos;
}

void Data_handler::setDataEvent() {
    while(cin >> event.time >> event.src_id >> event.dst_id)
        data_packet_event(event.src_id, event.dst_id, event.time);
}

void Data_handler::setCtrlEvent() {
    unsigned con_id = (node::getNodeNum() - 1); // now, nodeNum = number of node + 1(controller)
    string msg;
    unsigned int next_id;

    for(unsigned int i = 0; i < node_num; i++) {
        unsigned int node_id = i; // current node id to update

        // installation
        for(unsigned int j = 0; j < dst_num; j++) {
            // don't create a packet if the destination of node is itself 
            unsigned int cur_dst_id = dest_list[j];
            if(node_id == cur_dst_id)
                continue;

            msg = "install";
            next_id = node_list.at(i).old_table.at(cur_dst_id);
            ctrl_packet_event(con_id, node_id, cur_dst_id, next_id, inst_time, msg);

            msg = "update";
            next_id = node_list.at(i).new_table.at(cur_dst_id);
            ctrl_packet_event(con_id, node_id, cur_dst_id, next_id, updt_time, msg);
        }
    }
}

int main()
{       
    /******************************************
     * reassign the file pointers: test case1 *
     ******************************************/
    // freopen(".\\samples-Hw3\\1.in","r", stdin);
    // freopen(".\\output1.txt","w", stdout);

    /******************************************
     * reassign the file pointers: test case2 *
     ******************************************/
    // freopen(".\\samples-Hw3\\2.in","r",stdin);
    // freopen(".\\output2.txt","w",stdout);

    Data_handler handler;
    handler.startSetup();

    // start simulation!!
    event::start_simulate(handler.get_dur_time());
    // event::flush_events() ;
    // cout << packet::getLivePacketNum() << endl;
    return 0;
}