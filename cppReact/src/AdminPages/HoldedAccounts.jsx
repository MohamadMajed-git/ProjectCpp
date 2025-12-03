import { useEffect, useState } from "react";
import axiosClient from "../axiosClient";

export default function HoldedAccounts() {
  const [data,setData]=useState();
  const [reload,setReload]=useState(false);
    useEffect(()=>{
  axiosClient.get("/holded-accounts")
  .then(response=>
  {
    setData(response.data.accounts);
  }).catch(error=>
    {
      console.log(error);
    }
  );

  },[reload]);

  const handleActive=()=>{
    axiosClient.post("/holded-accounts/activate")
    .then(response=>
    {
      setReload(!reload);
      console.log(response);
    })
  }

  const handleDelete=()=>{
    axiosClient.post("/holded-accounts/delete")
    .then(response=>
    {
      setReload(!reload);
      console.log(response);
    })
  }

  return (
    <div>
      {data&&data.map((account,index)=>
      {
        const isFirst=index==0;
        return(
          <div key={index}>
            <div className="flex gap-2">
        <div>{account.email}</div>
        <div>{account.name}</div>
        <div>{account.creationDate}</div>
        <button 
        disabled={!isFirst}
        className={`${index==0?"bg-blue-500 hover:bg-blue-400":"bg-gray-500 disabled"}  p-1 m-1 text-sm text-white `}
        onClick={handleActive}
        >Activate</button>
        <button
        disabled={!isFirst}
        className={`${index==0?"bg-red-500 hover:bg-red-400":"bg-gray-500 disabled"} p-1 m-1 text-sm text-white `}
        onClick={handleDelete}
        >delete account</button>
        </div>
        </div>
      );
      })}
    </div>
  );
}