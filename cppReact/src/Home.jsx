import { useRef, useState } from "react";
import axiosClient from "./axiosClient";

export default function Home() {
    const nameRef = useRef();
    const number1Ref = useRef();
    const number2Ref = useRef();
    const [name, setName] = useState('');
    const [sum, setSum] = useState(null);
    const handleSubmit = () => {
        axiosClient.post('/submit', {
            name: nameRef.current.value
        })
            .then(response => {
                setName(response.data.message);
            })
    };
    const handleSummation = () => {
        axiosClient.post('/sum', {
            number1: number1Ref.current.value,
            number2: number2Ref.current.value
        })
            .then(response => {
                setSum(response.data.sum);
            })
    };
    return (
        <>
            <h1 className="text-2xl font-bold text-green-600">Welcome to the Home Page</h1>
            <div>
                <input ref={nameRef} type="text" className="border border-gray-300 p-2 m-2 rounded-md focus:outline-none" />
                <button className="bg-blue-500 text-white p-2 rounded-md hover:bg-blue-600"
                    onClick={handleSubmit}
                >Submit</button>
            </div>
            <div>
                {name && <p className="text-lg text-purple-700 mt-4">Response from server: {name}</p>}
            </div>
            <div>
                <input ref={number1Ref} type="text" className="border border-gray-300 p-2 m-2 rounded-md focus:outline-none" />
                <input ref={number2Ref} type="text" className="border border-gray-300 p-2 m-2 rounded-md focus:outline-none" />
                <button className="bg-blue-500 text-white p-2 rounded-md hover:bg-blue-600"
                onClick={handleSummation}
                >Submit</button>
            </div>
            <div>
                {sum && <p className="text-lg text-purple-700 mt-4">Response from server: {sum}</p>}    
            </div>
        </>
    );
}