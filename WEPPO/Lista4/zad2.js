class Tree {
    constructor(left, right, val) {
        this.val = val;
        this.left = left;
        this.right = right;
    }

    *tree(root) {
        if (root.left !== null)
            yield* root.tree(root.left);

        yield root.val;

        if (root.right !== null)
            yield* root.tree(root.right);
    }

    [Symbol.iterator]() {
        return this.tree(this);
    }
}

// function *tree(root){
//     if(root.left !== null)
//        yield* tree(root.left);

//     yield root.val;

//     if(root.right !== null)
//         yield* tree(root.right);
// }

var root = new Tree(new Tree(new Tree(null, new Tree(null, new Tree(null, null, 5), 4), 3), null, 2), null, 1);

for (var e of root) {
    console.log(e);
}