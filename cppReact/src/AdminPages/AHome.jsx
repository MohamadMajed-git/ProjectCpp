import { useEffect } from "react";
import axiosClient from "../axiosClient";
import { useNavigate } from "react-router-dom";

export default function AHome() {
  const navigate = useNavigate();



  return (
    <div>
      <h1 className="text-2xl font-bold">Admin Home</h1>
      <button className="bg-blue-500 rounded p-2 hover:bg-blue-400"
      onClick={()=>navigate("/admin/holded-accounts")}
      >HoldedAccounts</button>
    </div>
  );
}