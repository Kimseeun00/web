class Person{
    constructor(name,hp){
        this.name = name;
        this.hp = hp;
    }

    hello(){
        console.log(this.name);
    }
}

class Avengers extends Person{
    constructor(name, hp, power,skill){
        super(name,hp);
        this.power = power;
        this.skill = skil;
    }

    information(){
        console.log(this.name,this.power,this.sill)
    }
    
    fly(){
        console.log("비행 중");
    }
}
const ironMan = new Avengers("아이언맨", 100,1000,"미사일");
ironMan().information();
ironMan().fly();
