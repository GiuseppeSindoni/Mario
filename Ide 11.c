#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
        int key; //int weight;
        struct edge * next;
} Edge;

typedef struct graph {
    int V;
    Edge ** Adj;

} Graph;

Edge *newEdge (int k);
Graph * newGraph (int n);
void linkEdge (Graph *G,int idx, int key);
void addEdge(Graph * G );
void printGraph (Graph G);
void free_graph(Graph * G);

int main()
{ 
    Graph * G = newGraph(3);
    
    linkEdge(G,0,2);
    linkEdge(G,2,0);
    linkEdge(G,1,2);
    
    printGraph(*G);
    
    free_graph(G);
    return 0;
}

 Edge *newEdge (int k)
    {
       Edge * newE = malloc (sizeof(Edge));

       newE->key = k;
       //newE->weight = w;
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

void linkEdge (Graph *G,int idx, int key)
    {
     if(G != NULL && idx <= G->V - 1)
        {
         Edge* e= newEdge(key);
         if(e != NULL)
            {
                e->next = G->Adj[idx];
                G->Adj[idx]= e;
            }
        }
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
              {printf("%d -> ", e->key);
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
