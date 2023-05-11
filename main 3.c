#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
        int key; int weight;
        struct edge * next;
} Edge;

typedef struct graph {
    int V;
    Edge ** Adj;

} Graph;

Edge *newEdge (int k, int w);
Graph * newGraph (int n);
void linkEdge (Graph *G,int idx, int key, int w);
void addEdge(Graph * G );
void printGraph (Graph G);
void free_graph(Graph * G);
Edge * there_is(Graph * G,int n, int idx);
Graph * union_graph(Graph *, Graph *);
void union1(Graph * , Graph *);
int max(int,int);

int main()
{ 
    Graph * g1 = newGraph(3);
    
    linkEdge(g1,0,2,5);
    linkEdge(g1,2,0,10);
    linkEdge(g1,1,0,1);
    linkEdge(g1,0,1,20);
    linkEdge(g1,1,1,40);

    printGraph(*g1);
    
    Graph *g2 = newGraph(4);

    linkEdge(g2,1,2,13);
    linkEdge(g2,0,2,3433);
    linkEdge(g2,2,1,133);
    linkEdge(g2,0,3,10);
    linkEdge(g2,6,1,123);

    printGraph(*g2);
    
    Graph * g3 = union_graph(g1,g2);
    printGraph(*g3);

    free_graph(g1); free_graph(g2); free_graph(g3);
    return 0;
}

int max(int i, int j)
    {
        if(i > j) 
            return i; 
        
        return j;
    }

Graph * union_graph (Graph *g1, Graph * g2)
    {
        Graph * g3 = newGraph(max(g1->V,g2->V));

        union1(g1,g3); 
        union1(g2,g3);

        return g3;

    }

void union1(Graph * sor, Graph *dest)
    {
     for (int i = 0; i < sor->V; i++)
        {
         Edge * e = sor->Adj[i];

         while(e != NULL)
            {
             linkEdge(dest,i,e->key,e->weight);
              e= e->next;
            }


        } 
         


    }

 Edge *newEdge (int k, int w)
    {
       Edge * newE = malloc (sizeof(Edge));

       newE->key = k;
       newE->weight = w;
       newE->next = NULL;

       return newE;

    }

Graph * newGraph (int n)
    {
     Graph * newG = malloc(sizeof(Graph));
     if(newG != NULL)
         {newG->V = n;
          newG->Adj = malloc(newG->V*sizeof(Edge*));

         for(int i = 0; i < newG->V; i++)
             {
              newG->Adj[i] = NULL;
             }
         }
     return newG;
    }

Edge * there_is(Graph * G, int n, int idx)
    {
        Edge * nodo= G->Adj[idx];

        while(nodo != NULL)
            {//printf("%d ",nodo->key) ;
             if(nodo->key == n)
                return nodo;
             nodo = nodo->next;
            }
        //printf ("NULL.\n");
        return NULL;


    }

void linkEdge (Graph *G,int idx, int key, int w)
    {
     if(G != NULL && idx < G->V && key < G->V)
       if(w > 0)
        {
         Edge* e= newEdge(key,w);

         if(e != NULL)
            { Edge * n = there_is (G,e->key,idx);
                if(n == NULL)
                    {e->next = G->Adj[idx];
                    G->Adj[idx]= e;}
                else
                   n->weight += w;
            }
         else 
             printf("Impossibile creare un nuovo nodo!!!\n\n");
        }
        else
            printf("Il peso deve essere maggiore di 0.\n\n");
    else
        printf("Non e' possibile linkare il nodo %d, perche non appartiene al Grafo. \n\n",idx);
    }

void addEdge(Graph * G )
    {
     Edge ** newAdj = realloc(G->Adj,sizeof(Edge *) * G->V+1);

     if(newAdj != NULL)
     { 
        G->Adj = newAdj;
        G->Adj[G->V-1] = NULL;
        G->V ++;
     }
    }


void printGraph (Graph G)
    {
     for(int i = 0; i < G.V; i++)
         {
          printf("%d: ",i);
          Edge* e = G.Adj[i];

          while( e != NULL )
              {printf("%d|%d -> ", e->key, e->weight);
               e = e->next;
              }

          printf("\n\n");
     }
    }
    
void free_graph(Graph *G)
    {
        
    if(G != NULL && G->V >0)    
     { Edge *e, *enext;
       for(int i = 0; i < G->V; i++)
        {
            e= G->Adj[i]; enext = NULL;
            
            while(e != NULL)
                {
                 enext= e->next;
                 free(e);
                 e= enext;
                }
            
        }
     free(G->Adj); free(G);
     }  
    }