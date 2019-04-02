var example = {
    name: "Kamil",
    hello: function(){
        console.log("Hello " + example.name);
    },
    get n(){
        return example.name;
    },
    set n(n){
        example.name = n;
    }
}

Object.defineProperty(example, 'surname', {
    value: 'Woś'
});
Object.defineProperty(example, 'newHello', {
    value: function(){
        console.log ("Hello " + example.name + " " + example.surname);
    }
});
Object.defineProperty(example, 'info', {
    get(){
        return this.name + " " + this.surname;
    },
    set(s){
        this.name = s;
    }
});
example.info = "Tomek";
console.log(example.info);

