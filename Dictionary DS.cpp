  #include <iostream>
  #include <stdlib.h>
  #include <fstream>
  #include <string.h>
  #include <cstdio>
  
  using namespace std;

ofstream myfile;
  struct BSTnode {
        char word[128], meaning[256];
        struct BSTnode *left, *right;
  };

  struct BSTnode *root = NULL;

  struct BSTnode * createNode(char *word, char *meaning) {
        struct BSTnode *newnode;
        newnode = (struct BSTnode *)malloc(sizeof(struct BSTnode));
        strcpy(newnode->word, word);
        strcpy(newnode->meaning, meaning);
        newnode->left = newnode->right = NULL;
        return newnode;
  }

  void insert(char *word, char *meaning) {
        struct BSTnode *parent = NULL, *current = NULL, *newnode = NULL;
        int res = 0;
        if (!root) {
                root = createNode(word, meaning);
                return;
        }
        for (current = root; current !=NULL;
           current = (res > 0) ? current->right : current->left) {
                res = strcasecmp(word, current->word);
                if (res == 0) {
                        cout<<"Duplicate entry!!\n";
                        return;
                }
                parent = current;
        }
        newnode = createNode(word, meaning);
        res > 0 ? (parent->right = newnode) : (parent->left = newnode);
        return;
  }

  void deleteNode(char *str) {
        struct BSTnode *parent = NULL, *current = NULL, *temp = NULL;
        int flag = 0, res = 0;
        if (!root) {
                cout<<"BST is not present!!\n";
                return;
        }
        current = root;
        while (1) {
                res = strcasecmp(current->word, str);
                if (res == 0)
                        break;
                flag = res;
                parent = current;
                current = (res > 0) ? current->left : current->right;
                if (current == NULL)
                        return;
        }
        /* deleting leaf node */
        if (current->right == NULL) {
                if (current == root && current->left == NULL) {
                        free(current);
                        root = NULL;
                        return;
                } else if (current == root) {
                        root = current->left;
                        free (current);
                        return;
                }

                flag > 0 ? (parent->left = current->left) :
                                (parent->right = current->left);
        } else {
                /* delete node with single child */
                temp = current->right;
                if (!temp->left) {
                        temp->left = current->left;
                        if (current == root) {
                                root = temp;
                                free(current);
                                return;
                        }
                        flag > 0 ? (parent->left = temp) :
                                        (parent->right = temp);
                } else {
                        /* delete node with two children */
                        struct BSTnode *successor = NULL;
                        while (1) {
                                successor = temp->left;
                                if (!successor->left)
                                        break;
                                temp = successor;
                        }
                        temp->left = successor->right;
                        successor->left = current->left;
                        successor->right = current->right;
                        if (current == root) {
                                root = successor;
                                free(current);
                                return;
                        }
                        (flag > 0) ? (parent->left = successor) :
                                        (parent->right = successor);
                }
        }
        free (current);
        return;
  }

  void findElement(char *str) {
        struct BSTnode *temp = NULL;
        int flag = 0, res = 0;
        if (root == NULL) {
                cout<<"Binary Search Tree is out of station!!\n";
                return;
        }
        temp = root;
        while (temp) {
                if ((res = strcasecmp(temp->word, str)) == 0) {
                        cout<<"Word   : "<< str;
                        cout<<" Meaning: "<< temp->meaning;
                        flag = 1;
                        break;
                }
                temp = (res > 0) ? temp->left : temp->right;
        }
        if (!flag)
                cout<<"Search Element not found in Binary Search Tree\n";
        return;
  }

  void inorderTraversal(struct BSTnode *myNode) {
        if (myNode) {
                inorderTraversal(myNode->left);
                cout<<"Word : "<< myNode->word<<" ";
                cout<<"|Meaning :"<< myNode->meaning<<endl; 
                inorderTraversal(myNode->right);
        }
        return;
  }
  
   void save(struct BSTnode *myNode) {
        if (myNode) {
                save(myNode->left);
                myfile << myNode->word<<" "<< myNode->meaning<<"\n";   
                save(myNode->right);
        }
        return;
  }
	
  int main() {
        int ch,a=0;
        char str[128], meaning[256];
        string STRING;
        string sub;
        string start;
        
	    ifstream infile;
	    infile.open ("test.txt");
			    
	    string previousLine="";
	    
	    while(getline(infile, STRING)) // To get you all the lines.
	    {    
	    	int pos = STRING.find(" "); 	
			
	    	start= STRING.substr(0 ,pos);     	
			sub= STRING.substr(pos + 1); 
				    	
	    	char cstart[start.size() + 1];
			strcpy(cstart, start.c_str());
	    	
	    	char csub[sub.size() + 1];
			strcpy(csub, sub.c_str());
	    	
	    	insert(cstart,csub);
	
	    }
	    infile.close();
	    myfile.open ("test.txt"); 
        while (1) {
                cout<<"\n1. Insertion\t2. Deletion\n";
                cout<<"3. Searching\t4. Traversal\n";
                cout<<"5. Exit\nEnter ur choice:";
                cin>>ch;
                getchar();
                switch (ch) {
                        case 1:
                                cout<<"Word to insert:";
                                //fgets(str, 100, stdin);
                                cin.get(str, 100);
                                cin.sync();
                                cout<<"Meaning:";
                                cin.get(meaning, 256);
                                //cin.clear();
                               // fgets(meaning, 256, stdin);
                                insert(str, meaning);
                                break;
                        case 2:
                                cout<<"Enter the word to delete:";
                                cin.get(str, 100);
                                cin.sync();
                                deleteNode(str);
                                break;
                        case 3:
                                cout<<"Enter the search word:";
                                cin.get(str, 100);
                                cin.sync();
                                findElement(str);
                                break;
                        case 4:
                                inorderTraversal(root);
                                break;
                        case 5:                     		
                        		save(root);                        		
                                exit(0);
                                break;
                        default:
                                cout<<"You have entered wrong option\n";
                                break;
                }
        }
        myfile.close();
        return 0;
  }
