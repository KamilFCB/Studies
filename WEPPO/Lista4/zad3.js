var Foo = (function(){

    this.Qux = function(){
        console.log("qux");
    }
    
    return{
        Bar: function(){
            Qux();
        }
    }
})();

var f = Foo;
f.Bar();
console.log(f.Qux);
