import axios from "axios";


const axiosClient = axios.create({
    baseURL: "https://projectcpp123.onrender.com/api",
});

export default axiosClient;