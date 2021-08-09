#include<bits/stdc++.h>
using namespace std;

class Trie{
    public:
        Trie *small_letters[26];
        bool end_of_the_word;
        string meaning;
};

Trie *create_new_leaf()
{
    int i;
    Trie *trie;
    trie = new Trie();

    for(i=0;i<26;i++)
    {
        trie->small_letters[i] = NULL;
    }

    trie->end_of_the_word = false;

    return trie;
}

void insert_into_trie(Trie *trie,string &word,string &meaning)
{
    int i;

    for(i=0;i<word.size();i++)
    {
        int index_root = word[i] - 'a';

        if(trie->small_letters[index_root] == NULL)
        {
            trie->small_letters[index_root] = create_new_leaf();
        }

        trie = trie->small_letters[index_root];
    }

    trie->end_of_the_word = true;
    trie->meaning = meaning;
}

bool check_for_feasible(string &word)
{
    for(int i=0;i<word.size();i++)
    {
        if(!(word[i] >= 'a' && word[i]<= 'z' ))
        {
            return false;
        }
    }
    return true;
}

bool search(Trie *trie,string &word)
{
    int i;

    if(trie==NULL)
        return " ";

    for(i=0;i<word.size();i++)
    {
        int root_index = word[i] - 'a';

        if(trie->small_letters[root_index]==NULL)
        {
            return false;
        }
        trie = trie->small_letters[root_index];
    }

    return (trie->end_of_the_word == true && trie!=NULL);
}

void print(string *sentence,int level)
{
    for(int i=0;i<level;i++)
    {
        cout<<sentence[i];
    }
    //cout<<"\n";
}

void display(Trie *trie, string *sentence , int level)
{
    if(trie->end_of_the_word == true)
    {
        print(sentence,level);

        cout<<"\t\t"<<trie->meaning;

        cout<<"\n\n";
    }

    for(int i=0;i<26;i++)
    {
        if(trie->small_letters[i] != NULL)
        {
            sentence[level] = char(i + 'a');
            display(trie->small_letters[i],sentence,level+1);
        }
    }
}


string insert(Trie *trie)
{
    int c,a=0;
    string word;

    cout<<"\n\nEnter the word to be inserted  :  ";
    cin.ignore();
    cin>>word;

    check_for_feasible(word) ? c = 1 : c = 0;

    if(c==1)
        {


            search(trie,word) ? a =1 : a = 2;

            if(a==1)
            {
                cout<<"\n\n The given word is already present in the trie, so it can not be inserted. \n\n";
                return "@" ;
            }
        }

    if(c==0)
        {
            cout<<"\n\nThe given word is not feasible  ";
            return "@";
        }

    return word;
}

int get_the_word(Trie *trie, string &word)
{
    int a = 0;
    search(trie,word) ?  a = 1 : a = 2;

    if(a==2)
    {
        cout<<"\n\n The entered word is NOT PRESENT IN THE TRIE  \n\n";
    }

    else{

        for(int i=0;i<word.size();i++)
        {
            int root_index = int (word[i]- 'a');

            if(trie->small_letters[root_index] == NULL)
            {
                cout<<"\n\n The entered word is NOT PRESENT IN THE TRIE  \n\n";
            }

            trie = trie->small_letters[root_index] ;
        }

        if(trie->end_of_the_word==true)
            cout<<trie->meaning;
    }

}

void print_suggestion_word(string *sentence,int level)
{
    for(int i=0;i<level;i++)
    {
        cout<<sentence[i];
    }
    cout<<"\n";
}

void print_suggestion(Trie *trie,int length,string *sentence)
{
    if(trie->end_of_the_word == true)
    {
        print_suggestion_word(sentence,length);

        cout<<"\n\n";
    }

    for(int i = 0 ;i<26;i++)
    {
        if(trie->small_letters[i] !=NULL)
        {
            sentence[length++] = char(i + 'a');
            print_suggestion(trie->small_letters[i],length+1,sentence);
        }
    }
}

void suggestion(Trie *trie,string &word,string *sentence)
{
    int length = word.size();

    for(int i=0;i<word.size();i++)
    {
        int root_index = int(word[i] - 'a' );

        if(trie->small_letters[root_index]==NULL)
        {
            cout<<"\n\n\n\t\tNo such suggestion can be given " ;
        }

        trie = trie->small_letters[root_index];
        sentence[i] = word[i];
    }

    print_suggestion(trie,length+1,sentence);
}

void insert_into_vector(vector<string>&v,string *sentence,int level)
{
    string s = " ";

    for(int i=0;i<level;i++)
    {
        s = s + sentence[i];
    }

    v.push_back(s);
}

void insert_pattern(Trie *trie,vector<string>&v,string *sentence,int level)
{
    if(trie->end_of_the_word == true)
    {
        insert_into_vector(v,sentence,level);
    }

    for(int i=0;i<26;i++)
    {
        if(trie->small_letters[i]!=NULL)
        {
            sentence[level] = char(i +'a');
            insert_pattern(trie->small_letters[i],v,sentence,level+1);
        }
    }
}

void search_pattern(Trie *trie,string &word, vector<string>&v)
{
    int count = 0,len = word.size();

    string alter;

    for(int i=0;i<v.size();i++)
    {
        alter = v[i];
        int found = alter.find(word);

        if(found != string::npos)
        {
            cout<<v[i]<<endl;
        }
    }

}

void pattern_searching(Trie *trie,string &word,string *sentence)
{
    vector<string>p_word;
    insert_pattern(trie,p_word,sentence,0);
    search_pattern(trie,word,p_word);
}

Trie *remove(Trie*trie, string word,int depth =0)
{

    if (!trie)
        return NULL;

    if (depth==word.size())
    {
        if (trie->end_of_the_word)
            trie->end_of_the_word=false;

        if (trie==NULL)
        {
            delete(trie);
            trie =NULL;
        }
        return trie;
    }
    int root_index=word[depth] - 'a';
    trie->small_letters[root_index]= remove(trie->small_letters[root_index],word,depth+1);

    if (trie==NULL&& trie->end_of_the_word==false)
    {

        delete (trie);
        trie=NULL;
    }
    return trie;
}



int main()
{
    string word,meaning;
    string i_word;
    string sentence[100];
    int option,a=0;
    bool c;

    Trie *trie = new Trie();
    trie = create_new_leaf();

    do
    {
        cout<<"\t\t\t\t \n\n\n ENTER THE OPERATION NUMBER TO BE PERFORMED \n\n";

        cout<<"1 - insertion into the trie "<<endl;
        cout<<"2 - search for a word whether it is persent or not "<<endl;
        cout<<"3 - print the content in the trie "<<endl;
        cout<<"4 - to get the meaning of the word "<<endl;
        cout<<"5 - to get the suggestions of the word "<<endl;
        cout<<"6 - To get the pattern of the word  "<<endl;
        cout<<"7 - Deletion \n"<<endl;
        cout<<"Other numbers to get exit \n\n";

        cout<<"\n\n ENTER THE OPERATION NUMBER TO BE PERFORMED  :  ";
        cin>>option;

        switch (option)
        {
        case 1:
                i_word = insert(trie);

                if((i_word.compare("@")))
                {
                    cout<<"\n\n\n Enter the meaning of the word  :  ";
                    cin.ignore();
                    getline(cin,meaning);

                    insert_into_trie(trie,i_word,meaning);
                    cout<<"\n\n\n\nWord successfully inserted \n\n ";
                }

            break;

        case 2: cout<<"Enter the word to be searched  :";
                cin>>word;

                c = check_for_feasible(word);

                if(c==true)
                    {
                        search(trie,word) ? a = 1 : a = 2;

                        if(a==1)
                        {
                                cout<<"\n\n\n\t\t\tEntered word is 'PRESENT IN THE TRIE' \n\n\n" ;
                        }

                        else
                        {
                            cout<<"\n\n\n\t\t\tEntered word 'IS NOT PRESENT IN THE TRIE' \n\n\n";
                        }
                    }

                break;

        case 3: cout<<"\n\n";
                cout<<"Word \t\t";
                cout<<"Meaning \n"<<endl;
                display(trie,sentence,0);
                break;

        case 4: cout<<"\n\n";
                cout<<"Enter the word to get its meaning  :  ";
                cin>>word;

                c = check_for_feasible(word);

                if(c==true)
                {
                    cout<<"The meaning of the entered word "<<word <<" is  :  ";
                    get_the_word(trie,word);
                }

                break;

        case 5: cout<<"\n\n";
                cout<<"Enter the word to get it's suggestions  :  ";
                cin>>word;

                c = check_for_feasible(word);

                if(c==true)
                {
                    cout<<"\n\nThe  Suggestions of the word  ' "<<word <<" '  are : "<<endl;
                    suggestion(trie,word,sentence);
                }
                break;

        case 6: cout<<"\n\n";
                cout<<"Enter the pattern to be searched  :  ";
                cin>>word;

                pattern_searching(trie,word,sentence);
                break;

        case 7: cout<<"Enter the word to be deleted \n";
                cin>>word;
                remove(trie,word);
                search(trie,word);
                cout<<"The word is  deleted\n\n";
                break;


        default:
            break;

        }
    } while(option <= 7);
}
