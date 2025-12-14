import { useEffect, useState } from "react";
import axiosClient from "../axiosClient";
import { useStateContext } from "../context/ContextProvider";

export default function PasswordChangeRequests() {
    const [passwordRequest,setPasswordRequest]=useState([]);
    const [reload,setReload]=useState(false);
    const {user}=useStateContext();
    useEffect(()=>{
        axiosClient.post("password-change-requests",{"email":user.email})
        .then(res=>{
            console.log(res);
            setPasswordRequest(res.data.requests);
        })
    },[reload]);


    const handleAcceptRequest=(email,newPassword)=>{
        axiosClient.post("approve-password-change",{
            "email":user.email,
            "userEmail":email,
            "newPassword":newPassword
        })
        .then(res=>{
            console.log(res);
            alert("Password Changed Successfully");
            setReload(!reload);
        })
        
    };
  return (
    <div>
        <h1 className="text-2xl font-bold">Password Change Requests Page</h1>
        {passwordRequest.length==0&&<p className="mt-4">No Password Change Requests</p>}
        {
            passwordRequest.length>0&&passwordRequest.map((request,index)=>
            {
                let lastIndex=passwordRequest.length-1;
                return(

                    <div key={index} className="border p-4 rounded mb-4">
                        <p>User Email: {request.email}</p>    
                        <p>Requested New Password: {request.password}</p>  
                        <button className={`mt-2 px-4 py-2 bg-green-600 text-white rounded-lg hover:bg-green-700 transition-colors duration-200 ${index!==lastIndex?"opacity-50 cursor-not-allowed":""}`}
                        onClick={()=>handleAcceptRequest(request.email,request.password)}
                        disabled={index!==lastIndex}
                        >

                            Accept Request
                        </button>          
                    </div>                

            )
            }
            )}
    </div>
  );
}