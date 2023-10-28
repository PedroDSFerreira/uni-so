# SO: Training exam

---

## Steps

1. Identify active entities (do second)

   - patient
   - nurse
   - doctor

2. Identify shared memory (do first)

   - Screening queue
   - Waiting line (priority queue)

3. Comunication between active entities (do third)

   - doctor (broadcast) -> patient (wait)

4. Safe termination (do last)
   - Release resources and exit (send dummy patients to doctors and nurses' queues)
