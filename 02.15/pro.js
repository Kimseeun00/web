const express = require("express");

const app = express();
const PORT = 8080;


const morgan = require("morgan");
app.use(morgan("dev"));


app.use(express.json());

app.use("/public", express.static("public"));
const multer = require("multer");

const upload = multer({
    storage: multer.diskStorage({
        destination: (req, file, done) => {
            done(null, "public/");
        },
        filename: (req, file, done) => {
            done(null, file.originalname);
        },
    }),
    limits: { fileSize: 5 * 1024 * 1024},
});

app.post("/api/file", upload.single("file"),(req, res) => {
    return res.json({test: "OK"});
});

app.listen(PORT, () => console.log(`this server listening on ${PORT}`));