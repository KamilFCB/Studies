module.exports = {
    Foo : function(){
        console.log('Moduł A');
        var moduleB = require('./zad4_moduleB.js');
        moduleB.Bar();
    },
    Bar : function(){
        console.log("Wywołanie z modułu B");
    }
}