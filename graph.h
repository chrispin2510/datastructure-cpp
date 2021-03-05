#ifndef GRAPH_H 
#define GRAPH_H 

#include <iostream>

const int INF = INT16_MAX;

typedef struct Node {
    int id;
    int weight;
    Node *link;
} * Node_T;

/* ==============================================
    Heap 
   ============================================== */
class Heap 
{
public:
    Heap(int capacity = 1);
    ~Heap();
    Heap(const Heap&);
    Heap& operator=(const Heap&);
    void set_capacity(int);
    int get_size() const;
    bool is_empty() const;
    void insert_min_heap(const Node_T&);
    void create_min_heap(const void *);
    Node_T delete_min_heap();
    void clear();
protected:
    int capacity;
    int size;
    Node_T *heap;
    void create_heap();
};

Heap::Heap(int capacity)
{
    set_capacity(capacity);
    create_heap(); 
    size = 0;
}

Heap::~Heap() 
{
    delete[] heap;
    heap = nullptr;
}

Heap::Heap(const Heap& x)
{
    set_capacity(x.capacity);
    create_heap();
    if (size > x.size)  {
        for (int i = 0; i < x.size; i++)
            heap[i] = x.heap[i];
    }
    else {
        for (int i = 0; i < size; i++)
            heap[i] = x.heap[i];
    }
}

Heap& Heap::operator=(const Heap& x)
{
    if (this == &x) 
        return *this;
    if (size >= x.size) {
        for (int i = 0; i < x.size; i++)
            heap[i] = x.heap[i];
    }
    else {
        for (int i = 0; i < size; i++)
            heap[i] = x.heap[i];
    }
    return *this;
}

bool Heap::is_empty() const
{
    return get_size() == 0;
}

void Heap::clear() 
{
    for (int i = 1; i <= size; i++)
        heap[i] = nullptr;
}

void Heap::set_capacity(int capacity)
{
    if (capacity <= 0)
        throw "The capacity of the heap should be > 0";
    this->capacity = capacity;
}

void Heap::create_heap()
{
    heap = new Node_T[capacity];
}

void Heap::insert_min_heap(const Node_T& x)
{
    if (size == capacity) {
        std::cerr << "Heap is full. \n";
        exit(EXIT_FAILURE);
    }
    int i = ++size;
    while ((i != 1) && (x->weight < heap[i/2]->weight)) {
        heap[i] = heap[i/2];
        i /= 2;
    }
    heap[i] = x;
}

Node_T Heap::delete_min_heap()
{
    if (!size) {
        std::cerr << "The heap is empty. \n";
        exit(EXIT_FAILURE);
    } 
    Node_T item = heap[1];
    Node_T temp = heap[size--];
    int p = 1;
    int i = 2;
    while (i <= size) {
        if ((i < size) && (heap[i]->weight > heap[i+1]->weight))
            i++;
        if (temp->weight <= heap[i]->weight) break;
        heap[p] = heap[i];
        p = i;
        i *= 2;
    }
    heap[p] = temp;
    return item;
}

int Heap::get_size() const
{
    return size;
}

void Heap::create_min_heap(const void * a)
{
    for (int i = 0; i < capacity-1; i++)
        insert_min_heap(((Node_T*)a)[i]);
}

/* ==================================================
        Graph 
   ================================================== */

class Graph: public Heap
{
public:
    Graph(int V = 1, int E = 0);
    ~Graph();
    Graph(const Graph &);
    Graph &operator=(const Graph &);
    void add_edge(int src, int dest, int weight);
    void prim() const;
    void print() const;

private:
    int V;           // number of vertices
    int E;           // number of Edges
    Node_T *list;    // Adjacency list container
    int *included;
};

Graph::Graph(int V, int E)
{
    if (V <= 0)
        throw "Graph should have at least one node.";
    this->V = V;
    this->E = E;
    list = new Node_T[E + 1];  // vertices numbered startig from 1
    included = new int[V + 1];
}

Graph::~Graph()
{
    delete[] list;
    delete[] included;
    
}

Graph::Graph(const Graph &other)
{
    V = other.V;
    list = new Node_T[V];

    for (int i = 0; i < V; i++)
        list[i] = other.list[i];
}

Graph &Graph::operator=(const Graph &rhs) 
{
    if (this == &rhs) 
        return *this;
    if (V >= rhs.V) 
        for (int i = 0; i < rhs.V; i++)
            list[i] = rhs.list[i];
    else 
        for (int i = 0; i < V; i++)
            list[i] = rhs.list[i];
    return *this;
}

void Graph::add_edge(int src, int dest, int weight)
{
    Node_T node = new Node;
    node->id = dest;
    node->weight = weight;
    node->link = nullptr;

    if (list[src]) {
        Node_T current = list[src];
        while (current->link)
            current = current->link;
        current->link = node;
    }
    else {
        list[src] = new Node;
        list[src]->id = src;
        list[src]->weight = 0;
        list[src]->link = node;
    }
}

void Graph::prim() const 
 = 0{
    Node_T adj = list[1]->link;
    int prev_id = 1;
    included[prev_id] = 1;
    for (int i = 1; i <= V; i++) {
        Heap heap(V + 1);
        Node_T v = adj;
        while (v != nullptr) {
            if (!included[v->id])
                heap.insert_min_heap(v);
            v = v->link;
        }
        if (!heap.is_empty()) {
            Node_T min = heap.delete_min_heap();
            std::cout << "(" << prev_id << ", " << min->id << ")\n";
            adj = list[min->id]->link;
            prev_id = min->id;
        }
        included[prev_id] = 1;
        heap.clear();
    }
}

void Graph::print() const
{
    Node_T current;
    for (int i = 1; i <= V; i++) {
        if (list[i])
            current = list[i]->link;
        while (current) {
            std::cout << "(" << i
                      << ", " << current->id
                      << ", " << current->weight << ")\n";
            current = current->link;
        }
    }
}
/* =============================================
    End Graph
   ============================================= */

#endif /* GRAPH_H */