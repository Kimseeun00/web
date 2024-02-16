const express = require("express");
const app = express();
const PORT = 8080;

const infos = [
    {
        name: "나나",
        age: 12,
    },
    {
        name: "유진",
        age: 8,
    },
    {
        name: "재범",
        age: 40,
    },
];

app.get("/infos/names",(req, res)=>{
    const names = infos.map((element) => {return element.name});
    return res.json(names);
})

app.get("/infos/ages",(req, res)=>{
    const ages = infos.map((element) => {return element.age});
    return res.json(ages);
})

app.get("/infos/:id",(req, res)=>{
    const id = infos.params.id;
    return res.json(infos[id]);
})

app.listen(PORT, () => console.log(`this server listening on ${PORT}`));
