const mysql = require("mysql2/promise");

const pool = mysql.createPool({
    host : "13.125.82.142",
    user: "ssafy",
    password: "ssafy_1234",
    database : "ssafy",
    waitForConnections: true,
    connectionLimit:  10,
    queueLimit: 0,
})

module.exports = {pool};