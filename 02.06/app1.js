const userInfos = [
    {
        id : "jony123",
        name :"이자룡",
        age: 31,
    },
    {
        id : "sylvie123",
        name :"따리에 실비",
        age: 31,
    },
    {
        id : "nana006",
        name :"나나",
        age: 2,
    }
];

userInfos.forEach((userInfos) => {
    console.log(userInfos.name);
});

// 이름만 가져와서 배열로 만들고 싶어


// 가져와서 똑같은 사이즈로 만들어야 하면 맵 사용
//콜백으로 쓸 때는 화살표 함수 써라. 한번 쓰고 버릴거니까
const names = userInfos.map((userInfo) =>`${userInfo.name}ㅁㅁ`);

//console.log(names);

const nana = userInfos.filter((userInfo) => userInfo.id ==="nana006"
);
console.log(nana);

//깔끔하게 구하는 법 -0번 인덱스만 찝어서 가져오기
const nana = userInfos.filter((userInfo) => userInfo.id ==="nana006"
)[0];
console.log(nana);


const infos = [
    {
        name:"김창수",
        age: 30,
        family: ["할머니","아내","아들"],
    },
    {
        name:"이민주",
        age: 24,
        family: ["남편"],
    },
    {
        name:"박종식",
        age: 58,
        family: ["아들", "딸","손자"],
    },
];
infos.filter(info => info.age > 25 ).map(el =>el.name);
infos.filter(info => info.family.foreach === "아들" ||info.family.foreach === "딸").map(el=>el.name);




// 왜 안돼?

  
  // 안한서
  // const child = infos
  //   .filter(
  //     (info) =>
  //       info.family.filter((member) => (member === "아들") | (member === "딸"))
  //         .length > 0
  //   )
  //   .map((info) => info.name);
  
  // 이자룡
  // const parentNames = infos
  //   .filter((info) => {
  //     let hasChild = false;
  //     info.family.map((member) => {
  //       if (member === "아들" || member === "딸") {
  //         hasChild = true;
  //       }
  //     });
  //     return hasChild;
  //   })
  //   .map((parents) => parents.name);