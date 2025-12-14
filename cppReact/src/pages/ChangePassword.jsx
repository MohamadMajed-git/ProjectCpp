import { useRef } from "react";
import { useStateContext } from "../context/ContextProvider";
import axiosClient from "../axiosClient";

export default function ChangePassword() {
  const newPasswordRef = useRef();
  const oldPasswordRef = useRef();
  const {user}=useStateContext();
  const handleChangePassword = () => {
    axiosClient.post("/change-password",{
      "email":user.email,
      "newPassword":newPasswordRef.current.value,
      "oldPassword":oldPasswordRef.current.value
    }).then(res=>{
      console.log(res);
    })
  };
  return (
    <div>
      <div>
        <h1>Change Password Page</h1>
        <input type="password" ref={newPasswordRef} placeholder="Enter new password" className="border p-2 rounded mb-4"/>
        <input type="password" ref={oldPasswordRef} placeholder="old password" className="border p-2 rounded mb-4 ml-4"/>
        <button className="px-4 py-2 bg-blue-600 text-white rounded-lg shadow hover:bg-blue-700 transition"
        onClick={handleChangePassword}
        >Change Password</button>
      </div>
    </div>
  );
}