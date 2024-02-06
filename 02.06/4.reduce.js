//const datas = [1, 2, 3, 4, 5];

//const result = datas.reduce((acc, cur) => {
//console.log(`acc : ${acc}`);
//console.log(`cur : ${cur}`);
//return acc + cur;
//}, 0);

//filter 구현

const datas = [1, 2, 3, 4, 5];
const test = datas.reduce((acc, cur) => {
  //초기값은 정해줘야 특정 메서드 활용이 가능하다.
  if (cur === 2) {
    acc.push(cur);
  }
  return acc;
}, []);

//const arr = ["피카츄","라이츄","파이리","꼬부기","피카츄","파이리"];

const result = arr.reduce((acc, cur) => {
  if (acc[cur]) {
    acc[cur] = acc[cur] + 1;
  } else {
    acc[cur] = 1;
  }
  return acc;
}, {});

//const arr1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
//const result1 = arr1.map((data) => {
  //if (data % 2 === 0) {
    //return data * 10;
  //}
//});
// ????

arr1.filter(el => el % 2 === 0).map(el => el * 10);

const arr2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
const result2 = arr2.reduce((acc, cur) => {
  if (cur % 2 === 0) {
    acc.push(cur * 10);
  }
  return acc;
},[]);
