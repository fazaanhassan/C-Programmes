#include <stdio.h> 
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */
// Fazaan Hassan
const int Fsize=50;
int no_edges;
int no_nodes;
int i;
const int cases=10;
// Parse a formula and return appropiate value
int parse(char *g)
{/* return 1 if atomic, 2 if  neg, 3 if binary, 4 if exists, 5 if for all, ow 0*/
int rect=0; // counters for the square brackets and parenthesis; check if equal number of right and left.  
int rectright=0;
int squarel=0;
int squareright=0;
int binaryconn=0;
int position,a =0,numbeer=0;
int i,b,c,d,e;
int startfromone=0,start=0,starting=0,final=0;
for(position=0; g[position] != '\0'; ++position){
    if (g[position]== '[') {
      b=position+1;
      ++rect;
      if(g[b] != 'x')
        ++startfromone;
      if(g[b] != 'y')
        ++startfromone;
      if (g[b] != 'z')
        ++startfromone;
      if(startfromone != 2*rect)
        return 0;
  }
    if(g[position] == ']') {
      c=position-1;
      ++rectright; 
      if(g[c] != 'x')
        ++start;
      if(g[c] != 'y')
        ++start;
      if (g[c] != 'z')
        ++start;
      if(start != 2*rectright)
        return 0;  
  }
    if(g[position] == '(')
      ++squarel;
    if(g[position] == ')')
      ++squareright;
    if(g[position] == 'v' || g[position] == '^' || g[position] == '>')
      ++binaryconn;
    if(g[position] == 'X'){
      i=position+1;
      if(g[i] != '[')
        return 0;
      }
    if(g[position] == 'A') {
      d=position+1;
      a++;
      if(g[d] != 'x' )
        ++starting;
      if(g[d] != 'y')
        starting++;
      if(g[d] != 'z')
        starting++;
      if(2*a != starting)
        return 0;

      }
    if (g[position] == 'E') {
      e=position+1;
      numbeer++;
      if(g[e] != 'x')
        ++final;
      if(g[e] != 'y')
        ++final;
      if(g[e] != 'z')
        ++final;
      if(2*numbeer != final)
        return 0;
    }
}
  if(rect != rectright || squareright != squarel || (squarel+squareright) != 2*binaryconn)
      return 0;
  
      switch(g[0]) {

        case 'X':
          if(g[1] == '[' && g[4] == ']' && g[5] == '\0')
            return 1;
          else
            break;
      case '-':
        if(g[1] == 'X' && g[2] == '[' && g[5] == ']' && g[6] == '\0')
          return 2;
        else if(g[1] == '-')
          return 1;
        else
          break;
       case '(':
        if(binaryconn < 1)
          return 0;
        else
          return 3;
       case 'E':
        if(g[2] == 'X' || g[2] == 'E')
          return 4;
        else if(g[2] == '(' || g[2] == 'A')
          return 4;
        else
          return 0;
       case 'A':
        if(g[2] == 'X'|| g[2] == 'A')
          return 5;
        else if(g[2] == '(' || g[2] == 'E')
          return 5;
        else
          return 0;
      default:
        break;
    }
return 0;
}
//
int eval(char *nm, int edges[no_edges][2], int size, int V[3])
{
    /* returns 1 if formla nm evaluates to true in graph with 'size' nodes, no_edges edges, edges stored in 'edges', variable assignment V.  Otherwise returns 0.*/
    char* point =  nm;
    int startarraycurrentfield[3];
    int functiontokey = 0;
    int a,b, i;
    int recieve = 0;
    
    for(i = 0; i< 3; i++) startarraycurrentfield[i] = V[i];

    switch(*point)
    {
        case 'X':
            point += 2;
            switch(*point)
            {
                case 'y':
                    a = 1;
                    break;
                case 'z':
                    a = 2;
                    break;
                case 'x':
                    a = 0;
                    break;                    
            }
            point++;
            switch(*point)
            {
                case 'z':
                    b = 2;
                    break;
                case 'x':
                    b = 0;
                    break;
                case 'y':
                    b = 1;
                    break;
            }
            for(i = 0; i<no_edges; i++)
            {
                if (edges[i][0] == V[a] && edges[i][1] == V[b]) recieve = 1;
            }
            return recieve;
            break;
        case '-':
            point++;
            if(eval(point, edges, size, V) == 0) return 1;
            else return 0;
        case 'E':
            point++;
            switch(*point)
            {
                case 'x':
                    point++;
                    for(i=0; i<size; i++)
                    {
                        startarraycurrentfield[0] = i;
                        if (eval(point, edges, size, startarraycurrentfield) == 1) return 1;
                    }
                    return 0;
                    break;
                case 'y':
                    point++;
                    for(i=0; i<size; i++)
                    {
                        startarraycurrentfield[1] = i;
                        if (eval(point, edges, size, startarraycurrentfield) == 1) return 1;
                    }
                    return 0;
                    break;
                case 'z':
                    point++;
                    for(i=0; i<size; i++)
                    {
                        startarraycurrentfield[2] = i;
                        if (eval(point, edges, size, startarraycurrentfield) == 1) return 1;
                    }
                    return 0;
                    break;
            }
            break;
        case 'A':
            point++;
            switch(*point)
            {
                case 'x':
                    point++;
                    for(i=0; i<size; i++)
                    {
                        startarraycurrentfield[0] = i;
                        if (eval(point, edges, size, startarraycurrentfield) == 0) return 0;
                    }
                    return 1;
                    break;
                case 'y':
                    point++;
                    for(i=0; i<size; i++)
                    {
                        startarraycurrentfield[1] = i;
                        if (eval(point, edges, size, startarraycurrentfield) == 0) return 0;
                    }
                    return 1;
                    break;
                case 'z':
                    point++;
                    for(i=0; i<size; i++)
                    {
                        startarraycurrentfield[2] = i;
                        if (eval(point, edges, size, startarraycurrentfield) == 0) return 0;
                    }
                    return 1;
                    break;
            }
            break;
        case '(':
            point++;
            a = eval(point, edges, size, V);
            do
            {
                if(*point == '(') functiontokey++;
                if(*point == ')') functiontokey--;
                if((*point == '^' || *point == '>' || *point == 'v') && functiontokey == 0) break;
                point++;
            }
            while(1);
            b = eval(point+1, edges, size, V);
            switch(*point)
            {
                case '^':
                    if(a == 1 && b == 1) return 1;
                    else return 0;
                    break;
                case 'v':
                    if(a == 1 || b == 1) return 1;
                    else return 0;
                    break;
                case '>':
                    if (a == 1 && b == 0) return 0;
                    else return 1;
                    break;
            }
            break;
    }

    return 0;
}

int main()
{
  char *name=malloc(Fsize); /*create space for the formula*/
  FILE *fp, *fpout;
 
  /* reads from input.txt, writes to output.txt*/
 if ((  fp=fopen("input.txt","r"))==NULL){printf("Error opening file");exit(1);}
  if ((  fpout=fopen("output.txt","w"))==NULL){printf("Error opening file");exit(1);}

  int j;
  for(j=0;j<cases;j++)
    {
      fscanf(fp, "%s %d %d",name,&no_nodes,&no_edges);/*read number of nodes, number of edges*/
      int edges[no_edges][2];  /*Store edges in 2D array*/
      for(i=0;i<no_edges;i++)	 fscanf(fp, "%d%d", &edges[i][0], &edges[i][1]);/*read all the edges*/

      /*Assign variables x, y, z to nodes */
      int W[3];
      /*Store variable values in array
	value of x in V[0]
	value of y in V[1]
	value of z in V[2] */
      for(i=0;i<3;i++)  fscanf(fp, "%d", &W[i]);
      int p=parse(name); 
      switch(p)
	{case 0:fprintf(fpout,"%s is not a formula. \n ", name);break;
	case 1: fprintf(fpout,"%s is an atomic formula. \n ",name);break;
	case 2: fprintf(fpout,"%s is a negated formula. \n ",name);break;
	case 3: fprintf(fpout,"%s is a binary connective formula. \n ", name);break;
	case 4: fprintf(fpout,"%s is an existential formula. \n ",name);break;
	case 5: fprintf(fpout,"%s is a universal formula. \n ",name);break;
	default: fprintf(fpout,"%s is not a formula. \n ",name);break;
	}
  
      /*Now check if formula is true in the graph with given variable assignment. */
  if (parse(name)!=0){
  if (eval(name, edges, no_nodes,  W)==1)	fprintf(fpout,"The formula %s is true in G under W\n", name);
	   else fprintf(fpout,"The formula %s is false in G under W\n", name);
      }
    }

  fclose(fp);
  fclose(fpout);
  free(name);
  return(0);
}
        

        
