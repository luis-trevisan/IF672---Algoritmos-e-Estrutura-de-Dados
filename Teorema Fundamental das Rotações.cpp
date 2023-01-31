#include <iostream>
#include <cstdio>

using namespace std;

typedef struct node {
    struct node *left;
    int val;
    struct node *right;
} Node;

Node *bst_insert(Node *, int &);
Node *rotate_left(Node *);
Node *full_rotate_left(Node *, int &);
Node *rebalanced(Node *, int *, int &, int &, int &);
int height(Node *, bool &);
void pos_order(Node *, int *);

int main(void)
{
    int *t, tam, aux, L = 0, R = 0;
    bool is_avl = true;
    Node *s = nullptr;
    char input[11];

    while(true) {
        scanf(" %s", input);

        if(input[0] == '\n') {
            break;
        }

        tam = atoi(input);

        t = new int[tam];
        
        for(int i = 0; i < tam; i++) {
            cin >> aux;
            s = bst_insert(s, aux);
        }

        for(int i = 0; i < tam; i++) {
            cin >> t[i];
        }

        s = full_rotate_left(s, L);

        aux = 0;

        s = rebalanced(s, t, aux, L, R);

        cout << L << ' ' << R << '\n';

        pos_order(s, t);

        cout << s -> val << '\n';

        aux = height(s, is_avl);

        if(is_avl) {
            cout << "true\n\n";
        }
        else {
            cout << "false\n\n";
        }

        s = nullptr;
        R = 0;
        L = 0;
        is_avl = true;
        

        fgets(input, sizeof input, stdin);
    }

    return 0;
}

Node *bst_insert(Node *root, int &value) {
    if(root == nullptr) {
        Node *N;

        N = new(Node);

        N -> val = value;
        N -> left = nullptr;
        N -> right = nullptr;

        return N;
    }

    if(value < root -> val) {
        root -> left = bst_insert(root -> left, value);
        return root;
    }
    else {
        root -> right = bst_insert(root -> right, value);
        return root;
    }
}

Node *rotate_left(Node *root) {
    Node *R, *RL;

    R = new Node;
    RL = new Node;

    R = root -> right;
    RL = R -> left;
    R -> left = root;
    root -> right = RL;
    
    return R;
}

Node *rotate_right(Node *root) {
    Node *R, *RR;

    R = new Node;
    RR = new Node;

    R = root -> left;
    RR = R -> right;
    R -> right = root;
    root -> left = RR;
    
    return R;
}

Node *full_rotate_left(Node *root, int &L) {
    if(root -> right != nullptr) {
        root = rotate_left(root);
        root = full_rotate_left(root, L);
        L++;
    }
    else if(root -> left != nullptr) {
        root -> left = full_rotate_left(root -> left, L);
    }

    return root;
}

Node *rebalanced(Node *root, int *t, int &i, int &L, int &R) {
    if(root == nullptr) {
        return root;
    }

    while(root -> val > t[i]) {
        root = rotate_right(root);
        R++;
    }
    while(root -> val < t[i]) {
        root = rotate_left(root);
        L++;
    }

    i++;

    root -> left = rebalanced(root -> left, t, i, L, R);
    root -> right = rebalanced(root -> right, t, i, L, R);

    return root;
}

int height(Node *root, bool &is_avl) {
    int HL, HR;

    if(root == nullptr) {
        return 0;
    }

    HL = height(root -> left, is_avl);
    HR = height(root -> right, is_avl);

    if((HR - HL) > 1 || (HR - HL) < -1) {
        is_avl = false;
    }

    return 1 + max(HR, HL);
}

void pos_order(Node *root, int *t) {
    if(root == nullptr) {
        return;
    }

    pos_order(root -> left, t);
    pos_order(root -> right, t);

    if(root -> val == t[0]) {
        return;
    }

    cout << root -> val << ' ';
}
