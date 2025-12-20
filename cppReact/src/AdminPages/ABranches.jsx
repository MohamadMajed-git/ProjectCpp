import React, { useEffect, useState } from "react";
import axiosClient from "../axiosClient";



export default function ABranches() {
  const [branches, setBranches] = useState([]);
  const [search, setSearch] = useState("");
  const [showForm, setShowForm] = useState(false);
  const [isEdit, setIsEdit] = useState(false);
  const [currentBranch, setCurrentBranch] = useState({
    id: null,
    branch_name: "",
    location_link: "",
    phone: "",
    address: "",
  });
  console.log("Current Branch:", currentBranch);
  const loadBranches = async () => {
    try {
      const res = await axiosClient.get("/admin/branches");


      setBranches(res.data==null ? [] : res.data);
    } catch (err) {
      console.error(err);
    }
  };

  useEffect(() => {
    loadBranches();
  }, []);

  const handleInput = (e) => {
    setCurrentBranch({
      ...currentBranch,
      [e.target.name]: e.target.value,
    });
  };

  const handleAdd = () => {
    setCurrentBranch({
      id: null,
      branch_name: "",
      location_link: "",
      phone: "",
      address: "",
    });
    setIsEdit(false);
    setShowForm(true);
  };

  const handleEdit = (branch) => {
    setCurrentBranch(branch);
    setIsEdit(true);
    setShowForm(true);
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    try {
      if (isEdit) {
     
  await axiosClient.put("/admin/branches", {
  id: currentBranch.id,
  name: currentBranch.branch_name,
  location_link: currentBranch.location_link,
  phone: currentBranch.phone,
  address: currentBranch.address,
});

      } else {
       await axiosClient.post("/admin/branches", {
       name: currentBranch.branch_name,
       location_link: currentBranch.location_link,
       phone: currentBranch.phone,
       address: currentBranch.address,
});



      }
      setShowForm(false);
      loadBranches();
    } catch (err) {
      console.error(err);
    }
  };

  const handleDelete = async (id) => {
    if (!window.confirm("Are you sure you want to delete this branch?")) return;

    try {
     await axiosClient.delete("/admin/branches", {
  data: { id },
});

      loadBranches();
    } catch (err) {
      console.error(err);
    }
  };

  const filteredBranches = branches.filter((b) =>
    b.id.toString().includes(search)
  );

  return (
    <div className="min-h-screen bg-gray-100 p-8">
      <h1 className="text-3xl font-bold text-blue-700 mb-6 text-center">
        Admin Panel - Bank Branches
      </h1>

      {}
      <div className="flex justify-between mb-5">
        <input
          type="number"
          placeholder="Search by ID"
          className="w-1/3 p-2 border border-blue-400 rounded-lg"
          value={search}
          onChange={(e) => setSearch(e.target.value)}
        />

        <button
          onClick={handleAdd}
          className="bg-blue-600 text-white px-5 py-2 rounded-lg hover:bg-blue-700"
        >
          + Add Branch
        </button>
      </div>

      {}
      <div className="overflow-x-auto shadow-lg rounded-lg border">
        <table className="w-full text-center bg-white">
          <thead className="bg-blue-700 text-white">
            <tr>
              <th className="p-3">ID</th>
              <th className="p-3">Branch Name</th>
              <th className="p-3">Location Link</th>
              <th className="p-3">Phone</th>
              <th className="p-3">Address</th>
              <th className="p-3">Actions</th>
            </tr>
          </thead>
          <tbody>
            {filteredBranches.map((branch, i) => (
              <tr key={i} className="border-b hover:bg-blue-50">
                <td className="p-3">{branch.id}</td>
                <td className="p-3">{branch.name}</td>
                <td className="p-3">
                  <a
                    href={branch.location_link}
                    target="_blank"
                    className="text-blue-600 underline"
                  >
                    Open
                  </a>
                </td>
                <td className="p-3">{branch.phone}</td>
                <td className="p-3">{branch.address}</td>
                <td className="p-3 space-x-2">
                  <button
                    onClick={() => handleEdit(branch)}
                    className="bg-yellow-500 text-white px-3 py-1 rounded hover:bg-yellow-600"
                  >
                    Edit
                  </button>
                  <button
                    onClick={() => handleDelete(branch.id)}
                    className="bg-red-600 text-white px-3 py-1 rounded hover:bg-red-700"
                  >
                    Delete
                  </button>
                </td>
              </tr>
            ))}

            {filteredBranches.length === 0 && (
              <tr>
                <td colSpan="6" className="p-4 text-gray-500">
                  No Branches Found
                </td>
              </tr>
            )}
          </tbody>
        </table>
      </div>

      {}
      {showForm && (
        <div className="fixed top-0 left-0 w-full h-full bg-black/50 flex items-center justify-center">
          <form
            onSubmit={handleSubmit}
            className="bg-white p-6 rounded-xl shadow-xl w-96"
          >
            <h2 className="text-xl font-bold mb-4 text-blue-700">
              {isEdit ? "Edit Branch" : "Add New Branch"}
            </h2>

            <input
              type="text"
              name="branch_name"
              placeholder="Branch Name"
              className="w-full p-2 border rounded mb-3"
              value={currentBranch.name}
              onChange={handleInput}
              required
            />
            <input
              type="text"
              name="location_link"
              placeholder="Location Link"
              className="w-full p-2 border rounded mb-3"
              value={currentBranch.location_link}
              onChange={handleInput}
              required
            />
            <input
              type="text"
              name="phone"
              placeholder="Phone"
              className="w-full p-2 border rounded mb-3"
              value={currentBranch.phone}
              onChange={handleInput}
              required
            />
            <input
              type="text"
              name="address"
              placeholder="Address"
              className="w-full p-2 border rounded mb-3"
              value={currentBranch.address}
              onChange={handleInput}
              required
            />

            <div className="flex justify-between">
              <button
                type="button"
                onClick={() => setShowForm(false)}
                className="px-4 py-2 bg-gray-400 text-white rounded"
              >
                Cancel
              </button>
              <button
                type="submit"
                className="px-4 py-2 bg-blue-700 text-white rounded"
              >
                {isEdit ? "Update" : "Add"}
              </button>
            </div>
          </form>
        </div>
      )}
    </div>
  );
}   