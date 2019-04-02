class Tree{
    constructor(left, right, val){
        this.val = val;
        this.left = left;
        this.right = right;
    }
}

var root = new Tree(new Tree(new Tree(null, new Tree(null, new Tree(null, null, 5), 4), 3), null, 2), null, 1);
console.log(root);