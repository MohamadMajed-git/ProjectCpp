 
import React, { useEffect, useState } from "react";
import axiosClient from "../axiosClient";

export default function Branches() {
  const [branches, setBranches] = useState([]);
 


  const loadBranches = async () => {
    try {
      const res = await axiosClient.get("/user/branches"); // API لليوزر
      setBranches(res.data == null ? [] : res.data);
    } catch (err) {
      console.error(err);
    }
  };

  useEffect(() => {
    loadBranches();
  }, []);


  return (
    <div className="min-h-screen bg-blue-50 p-6">
      <h1 className="text-3xl font-bold text-blue-700 text-center mb-8">
        Our Branches
      </h1>

     

      {/* عرض الفروع */}
      <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-6">
        {branches.map((branch) => (
          <div
            key={branch.id}
            className="bg-white rounded-2xl shadow-md p-6 flex flex-col border border-blue-100 hover:shadow-xl transition"
          >
            <h2 className="text-xl font-semibold text-blue-700 mb-2">
              {branch.name}
            </h2>
            <p className="text-gray-700 mb-2">📍 {branch.address}</p>
            <p className="text-gray-700 mb-4">📞 {branch.phone}</p>
            <a
              href={branch.location_link}
              target="_blank"
              rel="noopener noreferrer"
              className="mt-auto bg-blue-600 text-white text-center py-2 rounded-xl hover:bg-blue-700 transition"
            >
              Open Location
            </a>
          </div>
        ))}

       
      </div>
    </div>
  );
}