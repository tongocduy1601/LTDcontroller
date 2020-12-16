<h1>A SMART LOW-TEMPERATURE FOOD DEHYDRATION SYSTEM</h1>
<h3>Introduce</h3>
<p>The dry food can be preserved for a longer duration and is less susceptible to spoilage caused by the growth of
bacteria, molds, and insects. One of the most common techniques for the dry food is the use of Low Temperature
Dehydration (LTD). LTD is a process of reducing moisture of food to low level in low temperature environments. The
dry food using LTD can improve palatability, digestibility, color, flavor and appearance [1]. In the industry, many
machines that embed the LTD technique for food preservation. Most of these machines are imported, stand-alone,
locally controlled and expensive [2][3]. These machines mainly operate continuously or periodically or fixed
conditions. It leads to wasting energy, decreasing the machine life expectancy, increasing labor cost. Most importantly,
it does not save the sensor data that can be used to improve the system for the next operation. </p>
<p>In this research, we target to build a SMART LTD System that supports centralized and real-time monitoring for
multiple LTD machines, high reliability, high availability and scalability as well as affordability for Vietnamese users.
Figure 1 shows an overview of a typical architecture of a SMART LTD system. It includes LTD controllers, a centralized
web server and a cell-phone app. The LTD controller controls the LTD machine based on the temperature and humidity
inside and outside of the dry room. It sends temperature and humidity information to the IoT server in real time via
Wifi/3G connectivity. The IoT server saves the data to the database for the future use and send them to the user app.
The user app that can run on an Android or iOS cellphone, is used to check the status of the current operation of the
LTD machines and to send new commands for any LTD controller.
</p>
<p>An individual LTD machine normally includes three fans, a heater, a heat-pump/dehydration machine and an LTD
controller. The LTD controller can sense the temperature and humidity inside and outside the dry room as well as can
control fans, the heater and heat-pump/dehydration machine adaptively. Moreover, the LTD controller can also
obtain commands from the user app to operate appropriately.
</p>
<p>Since the operations of the SMART LTD system based on temperature and humidity sensor located inside the dry
room, it becomes a single point of failure in this system. We use a triple redundancy technique that uses three sensors
connected to three pins of a processor in order to improve the system reliability. This system still operates if one
sensor fails. The failed sensor is notified to the system admin so that it will be replaced as soon as possible without
interrupting the LTD machine operation.</p>
<p>With the support of the SMART LTD system, we believe we can improve productivity, save energy and help Vietnamese
farmers preserving their food effectively resulting in improving agricultural product values</p>
<h3>An LTD controller operation</h3>
<ol>
<li>At the beginning, the heater will be turned on to warm the dry room. When the temperature inside the dry
room reaches a user-defined maximum temperature value, the heater will be stopped.</li>
<li>When the heater is on, the fan2 will be on as well to make the temperature of the air be evenly distributed
in the dry room</li>
<li>3. If the humidity inside the dry room is greater than a user-defined maximum humidity, the fan1 will be
turned on to transfer the humidity air from the dry room to the outside. We can control the speed of the
fan1. For example, when the humidity is about 90% or more, the fan1 will run in full speed. When 80%, the
fan will run at 80% of the full speed and so on</li>
<li>When the heat pump is on, the fan 3 is also on to help the heat pump work better</li>
<li>Please note that when the heater is on, the heat pump is off and vice versa</li>
<li>The user can set the timer so that the heater and heat pump can be turned on periodically. </li>
<li>The controller should add time out for each operation.
</li>
<li>The controller should have at least three humidity sensors and three temperature sensors for reliability
operations.</li>
</ol>
<h3>Implement</h3>
<ol>
<li>implement code for LTD Controller
</li>
<li>I simulate the heater, heat pump, and fans using LEDs.</li>
</ol>